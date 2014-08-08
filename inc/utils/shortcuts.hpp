#ifndef OLYMPUS__UTILS__SHORTCUTS
#define OLYMPUS__UTILS__SHORTCUTS

#include "window/window.hpp"
#include "render/screen.hpp"
#include "render/world.hpp"
#include "render/standard_render_engine.hpp"

namespace olympus {
    struct EasyWindow {
        Window *window;
        Screen *screen;
        World *world;
        RenderEngine *render_engine;
    };
    
    EasyWindow *create_easy_window(unsigned width, unsigned height);
    void destroy_easy_window(EasyWindow *easy_window);
    
    struct EasyScreen {
        Screen *screen;
        World *world;
        RenderEngine *render_engine;
    };
    
    EasyScreen *create_easy_screen();
    void destroy_easy_screen(EasyScreen *screen);
    
    struct EasyWorld {
        World *world;
        RenderEngine *render_engine;
    };
    
    EasyWorld *create_easy_world();
    void destroy_easy_world(EasyWorld *world);
};
#endif
