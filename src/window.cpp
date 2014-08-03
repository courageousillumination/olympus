#include "window.hpp"

using namespace olympus;

Window::Window(unsigned width, unsigned height, const char *title) :
    _width(width), _height(height) {
    _internal_window =  glfwCreateWindow(width, height, title, nullptr, nullptr);
    
    _key_callback = nullptr;
}

Window::~Window() {
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

void Window::set_keyboard_callback(void (* callback)(int, int, int, int)) {
    _key_callback = callback;
}