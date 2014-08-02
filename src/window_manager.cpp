#include "window_manager.hpp"

using namespace std;
using namespace olympus;

WindowManager::WindowManager() : _num_windows(0) {
}

WindowManager& WindowManager::get_instance() {
    static WindowManager _manager;
    return _manager;
}

WindowManager::~WindowManager() {
    destroy_all_windows();
}

Window *WindowManager::create_window(unsigned width, unsigned height) {
    return create_window(width, height, DEFAULT_WINDOW_TITLE);
}

Window *WindowManager::create_window(unsigned width, unsigned height, const char *title) {
    Window *window = new Window(width, height, title);
    _num_windows++;
    _windows.push_back(window);
    return window;
}

void WindowManager::destroy_window(Window *window) {
    for (vector<Window *>::iterator i = _windows.begin() ;
         i != _windows.end(); i++) {
        if (*i == window) {
            _windows.erase(i);
            _num_windows--;
            delete window;
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