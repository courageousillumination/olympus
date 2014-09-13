#include <iostream>
#include <exception>
#include <stdexcept>

#include "debug/logger.hpp"

#include "window/window_manager.hpp"

using namespace std;
using namespace olympus;

/**
 * This function will pass through GLFW errors to our logger.
 */
static void glfw_error_callback(int error, const char* description) {
    LOG(Logger::ERROR, "%s", description);
}

/**
 * We have a problem handling the way GLFW was set up to not be OOP. Specifically,
 * all callbacks must be static, they can't be instance methods. To get around this
 * we iterate over all windows and find the one that has a matching window before
 * we trigger the callback. This may introduce a slight lag if there are a lot of windows
 * but it should simplify the overall struture.
 */
void WindowManager::internal_key_callback(GLFWwindow* window, int key, int scancode,
                                                 int action, int mods) {
    std::vector<Window *> windows = get_instance().get_windows();
    for (auto w : windows) {
        if (w->_internal_window == window && w->_key_callback != nullptr) {
            w->_key_callback(w, key, scancode, action, mods);
        }
    }
}

WindowManager::WindowManager() {
    initialize_backend();
    LOG(Logger::DEBUG, "Initalized GLFW");
}

WindowManager& WindowManager::get_instance() {
    // Static variable that will only be initalized once.
    static WindowManager _manager;
    return _manager;
}

WindowManager::~WindowManager() {
    destroy_all_windows();
    destroy_backend();
}

void WindowManager::initialize_backend() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        LOG(Logger::ERROR, "Failed to initalize GLFW");
        throw std::runtime_error("Failed to initalize GLFW");
    }
}

void WindowManager::destroy_backend() {
    glfwTerminate();
}

Window *WindowManager::create_window(unsigned width, unsigned height) {
    return create_window(width, height, DEFAULT_WINDOW_TITLE);
}

Window *WindowManager::create_window(unsigned width, unsigned height, const char *title) {
    Window *window = new Window(width, height, title);
    //Configure callbacks
    glfwSetKeyCallback(window->_internal_window, internal_key_callback);
    _windows.push_back(window);
    
    LOG(Logger::DEBUG, "Set up a window of size %dx%d with title %s", width, height, title);
    
    return window;
}

void WindowManager::destroy_window(Window *window) {
    for (vector<Window *>::iterator i = _windows.begin() ;
         i != _windows.end(); i++) {
        if (*i == window) {
            _windows.erase(i);
            delete window;
            LOG(Logger::DEBUG, "Destroyed window");
            return;
        }
    }
}

void WindowManager::destroy_all_windows() {
    for (unsigned i = 0; i < _windows.size(); i++) {
        delete _windows[i];
    }
    _windows.clear();
}

void WindowManager::poll() {
    glfwPollEvents();
}

//TESTING functions

void WindowManager::simulate_keypress(Window *window, int key, int scancode, int actions, int mods) {
    if (window != nullptr) {
        internal_key_callback(window->_internal_window, key, scancode, actions, mods);
    }
}