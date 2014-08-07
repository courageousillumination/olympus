#include <GL/glew.h>

#include "debug/logger.hpp"
#include "render/mesh.hpp"

#include "window/window.hpp"

using namespace olympus;

Window::Window(unsigned width, unsigned height, const char *title) :
    _width(width), _height(height) {
    _internal_window =  glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    _key_callback = nullptr;
    
    glfwMakeContextCurrent(_internal_window);
    glewExperimental = GL_TRUE; 
    glewInit();
    LOG(Logger::DEBUG, "Initalized GLEW");
    
    const GLubyte* renderer = glGetString (GL_RENDERER); 
    const GLubyte* version = glGetString (GL_VERSION);
    
    LOG(Logger::INFO, "Renderer: %s", renderer);
    LOG(Logger::INFO, "OpenGL version supported %s", version);
    
    _screen = new Screen;
}

Window::~Window() {
    delete _screen;
    
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

static const GLfloat simple_square_verts[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

static const GLfloat simple_square_texcoords[] = {
    0.0, 0.0,
    0.0, 1.0,
    1.0, 0.0,
    1.0, 1.0
};

static Mesh *mesh = nullptr;

void Window::render() {
    glClear( GL_COLOR_BUFFER_BIT);
    
    if (mesh == nullptr) {
        mesh = new Mesh(2, Mesh::TRIANGLE_STRIP);
        mesh->set_vertex_attribute(0, 3, 4, simple_square_verts);
        mesh->set_vertex_attribute(1, 2, 4, simple_square_texcoords);
    }
    if (_screen != nullptr) {
        _screen->render();
        
        //Now that we've rendered to a framebuffer we can unbind it and bind the screen back
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glViewport(0,0,_width, _height);
        
        //Next we can just use the rendered framebuffer back to the screen.
        _screen->get_framebuffer()->get_color_texture()->bind();
        
        mesh->bind();
        mesh->draw();
    }
    //Finally we swap our buffers
    glfwSwapBuffers(_internal_window);
}