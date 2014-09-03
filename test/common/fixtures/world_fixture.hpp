#ifndef OLYMPUS__TEST__FIXTURES__WORLD
#define OLYMPUS__TEST__FIXTURES__WORLD

#include <unistd.h>

#include <gtest/gtest.h>

#include "olympus.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640


class WorldedTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window = olympus::WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        usleep(100000); //Give the window time to create
        screen = new olympus::Screen;
        window->add_screen(screen);
        
        world = new olympus::World;
        screen->set_world(world);
        
        render_engine = new olympus::StandardRenderEngine;
        screen->set_render_engine(render_engine);
    }
    
    virtual void TearDown() {
        delete render_engine;
        delete world;
        delete screen;
        olympus::WindowManager::get_instance().destroy_all_windows();
    }
    
    olympus::Window *window;
    olympus::Screen *screen;
    olympus::World *world;
    olympus::RenderEngine *render_engine;
};

#endif