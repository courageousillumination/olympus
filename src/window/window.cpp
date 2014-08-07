#include <GL/glew.h>

#include "debug/logger.hpp"

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

static GLfloat simple_square_texcoords[] = {
    0.0, 0.0,
    0.0, 1.0,
    1.0, 0.0,
    1.0, 1.0
};

static GLuint vao_id = 0;
static GLuint vertexbuffer = 0, vbo_cube_texcoords = 0;

void Window::render() {
    glClear( GL_COLOR_BUFFER_BIT);
    
    if (vao_id == 0) {
        glGenVertexArrays(1, &vao_id);
        glBindVertexArray(vao_id);
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(simple_square_verts), simple_square_verts, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        glGenBuffers(1, &vbo_cube_texcoords);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(simple_square_texcoords), simple_square_texcoords, GL_STATIC_DRAW);
        /* onDisplay */
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
        glVertexAttribPointer(
            1, // attribute
            2,                  // number of elements per vertex, here (x,y)
            GL_FLOAT,           // the type of each element
            GL_FALSE,           // take our values as-is
            0,                  // no extra data between each position
            0                   // offset of first element
        );
    }
    if (_screen != nullptr) {
        _screen->render();
        
        //Now that we've rendered to a framebuffer we can unbind it and bind the screen back
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //glViewport(0,0,_width, _height);
        
        //Next we can just use the rendered framebuffer back to the screen.
        _screen->get_framebuffer()->get_color_texture()->bind();
        glBindVertexArray(vao_id);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        //Finally we swap our buffers
        glfwSwapBuffers(_internal_window);
    }
}