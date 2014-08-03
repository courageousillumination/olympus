#include <iostream>

#include "olympus.hpp"

using namespace std;
using namespace olympus;

static void key_callback(Window *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE) {
        window->set_should_close(true);
    }
}

int main() {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(640, 480);
    window->set_keyboard_callback(key_callback);
    while(!window->should_close()) {
        window_manager.poll();
    }
    
}