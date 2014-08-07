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
    //Set up the logger
    StreamAppender *appender = new StreamAppender(std::cout);
    Logger::set_appender(appender);
    Logger::set_level(Logger::DEBUG | Logger::INFO);
    
    fps::enable_fps_logging(true);
    
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(640, 480);
    window->set_keyboard_callback(key_callback);
    
    while(!window->should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}