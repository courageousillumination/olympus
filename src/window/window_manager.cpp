#include <iostream>
#include <exception>
#include <stdexcept>

#include "debug/logger.hpp"

#include "window/window_manager.hpp"

using namespace std;
using namespace olympus;

static void glfw_error_callback(int error, const char* description)
{
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
    for (vector<Window *>::iterator i = windows.begin() ;
         i != windows.end(); i++) {
        if ((*i)->_internal_window == window) {
            if ((*i)->_key_callback != nullptr) {
                (*i)->_key_callback(*i, key, scancode, action, mods);
            }
        }
    }
}

WindowManager::WindowManager() : _num_windows(0) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initalize GLFW");
    }
    LOG(Logger::DEBUG, "Initalized GLFW");
}

WindowManager& WindowManager::get_instance() {
    static WindowManager _manager;
    return _manager;
}

WindowManager::~WindowManager() {
    destroy_all_windows();
    glfwTerminate();
}

Window *WindowManager::create_window(unsigned width, unsigned height) {
    return create_window(width, height, DEFAULT_WINDOW_TITLE);
}

Window *WindowManager::create_window(unsigned width, unsigned height, const char *title) {
    Window *window = new Window(width, height, title);
    //Configure callbacks
    glfwSetKeyCallback(window->_internal_window, internal_key_callback);
    _num_windows++;
    _windows.push_back(window);
    
    LOG(Logger::DEBUG, "Set up a window of size %dx%d with title %s", width, height, title);
    
    return window;
}

void WindowManager::destroy_window(Window *window) {
    for (vector<Window *>::iterator i = _windows.begin() ;
         i != _windows.end(); i++) {
        if (*i == window) {
            _windows.erase(i);
            _num_windows--;
            delete window;
            LOG(Logger::DEBUG, "Destroyed window");
            return;
        }
    }
}

void WindowManager::destroy_all_windows() {
    for (unsigned i = 0; i < _num_windows; i++) {
        delete _windows[i];
    }
    _windows.clear();
    _num_windows = 0;
}

void WindowManager::poll() {
    glfwPollEvents();
}

void WindowManager::simulate_keypress(Window *window, int key, int scancode, int actions, int mods) {
    if (window != nullptr) {
        internal_key_callback(window->_internal_window, key, scancode, actions, mods);
    }
}