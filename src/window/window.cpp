#include <exception>
#include <stdexcept>
#include <GL/glew.h>

#include "debug/logger.hpp"
#include "render/mesh.hpp"
#include "render/shaders.hpp"

#include "window/window.hpp"

using namespace olympus;


static const GLfloat simple_square_texcoords[] = {
    0.0, 0.0,
    1.0, 0.0,
    0.0, 1.0,
    1.0, 1.0
};

Window::Window(unsigned width, unsigned height, const char *title) :
    _width(width), _height(height) {
    _internal_window =  glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_internal_window == nullptr) {
        LOG(Logger::ERROR, "Failed to create GLFW window");
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    _key_callback = nullptr;
    
    glfwMakeContextCurrent(_internal_window);
    glewExperimental = GL_TRUE; 
    GLenum err = glewInit();
    if (err !=  GLEW_OK) {
        LOG(Logger::ERROR, "Failed to initalize GLEW. Errors %s", glewGetErrorString(err));
        throw std::runtime_error("Failed to initalize GLEW");
    }
    LOG(Logger::DEBUG, "Initalized GLEW");
    
    const GLubyte* renderer = glGetString (GL_RENDERER); 
    const GLubyte* version = glGetString (GL_VERSION);
    
    LOG(Logger::INFO, "Renderer: %s", renderer);
    LOG(Logger::INFO, "OpenGL version supported %s", version);
    
    glfwSwapInterval(1);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDisable(GL_CULL_FACE);
    
    //Build my renderer
    _renderer = new Renderer(TEXTURE_VERTEX_SHADER,
                            TEXTURE_FRAGMENT_SHADER);
}

Window::~Window() {
    for(std::vector<ScreenAndMesh>::iterator it = _screens.begin();
        it != _screens.end(); it++) {
        delete it->mesh;
    }
    delete _renderer;
    glfwDestroyWindow(_internal_window);
}

void Window::set_height(unsigned height) {
    set_dimensions(_width, height);
}
void Window::set_width(unsigned width) {
    set_dimensions(width, _height);
}
void Window::set_dimensions(unsigned width, unsigned height) {
    _width = width;
    _height = height;
    glfwSetWindowSize(_internal_window, _width, _height);
}

bool Window::should_close() {
    return glfwWindowShouldClose(_internal_window);
}
void Window::set_should_close(bool flag) {
    glfwSetWindowShouldClose(_internal_window, flag);
}

void Window::set_keyboard_callback(void (* callback)(Window *, int, int, int, int)) {
    _key_callback = callback;
}

void Window::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (auto screen : _screens) {
        screen.screen->render();
    }
    
    _renderer->bind();
    _renderer->set_uniform(std::string("model_view_matrix"), glm::mat4(1.0f));
    _renderer->set_uniform(std::string("projection_matrix"), glm::mat4(1.0f));
        
    for (auto screen : _screens) {
        screen.screen->get_framebuffer()->get_color_texture()->bind();
        screen.mesh->bind();
        screen.mesh->draw();
    }
    
    //Finally we swap our buffers
    glfwSwapBuffers(_internal_window);
}

void Window::add_screen(Screen *screen) {
    add_screen(screen, -1.0, -1.0, 2.0, 2.0);
    
}
void Window::add_screen(Screen *screen, float x, float y, float width, float height) {
    ScreenAndMesh screen_and_mesh;
    screen_and_mesh.screen = screen;
    
    //Create the mesh
    Mesh *mesh = new Mesh(2, Mesh::TRIANGLE_STRIP);
    
    const float verts[] = {
        x, y, 0.0,
        x + width, y, 0.0,
        x, y + height, 0.0,
        x + width, y + height, 0.0
    };
    
    mesh->set_vertex_attribute(0, 3, 4, verts);
    mesh->set_vertex_attribute(1, 2, 4, simple_square_texcoords);
    
    screen_and_mesh.mesh = mesh;
    _screens.push_back(screen_and_mesh);
}
void Window::remove_screen(Screen *screen) {
    for(std::vector<ScreenAndMesh>::iterator it = _screens.begin();
        it != _screens.end(); it++) {
        if (it->screen == screen) {
            delete it->mesh;
            _screens.erase(it);
            return;
        }
    }
}
