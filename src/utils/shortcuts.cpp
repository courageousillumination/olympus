#include "window/window_manager.hpp"

#include "utils/shortcuts.hpp"

using namespace olympus;

EasyWindow *olympus::create_easy_window(unsigned width, unsigned height) {
    EasyWindow *easy_window = new EasyWindow;
    
    WindowManager &window_manager = WindowManager::get_instance();
    easy_window->window = window_manager.create_window(width, height);
    
    //Create a screen to attach to the window
    easy_window->screen = new Screen;
    easy_window->window->add_screen(easy_window->screen);
    
    //Create a world to add to the screen
    easy_window->world = new World;
    easy_window->screen->set_world(easy_window->world);
    
    //Create a render engine for the world
    easy_window->render_engine = new StandardRenderEngine;
    easy_window->world->set_render_engine(easy_window->render_engine);
    
    return easy_window;
}
void olympus::destroy_easy_window(EasyWindow *easy_window) {
    delete easy_window->render_engine;
    delete easy_window->world;
    delete easy_window->screen;
    WindowManager::get_instance().destroy_window(easy_window->window);
    delete easy_window;
}