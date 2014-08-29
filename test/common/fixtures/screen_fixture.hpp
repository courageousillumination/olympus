#ifndef OLYMPUS__TEST__FIXTURES__SCREEN
#define OLYMPUS__TEST__FIXTURES__SCREEN

#include <unistd.h>

#include <gtest/gtest.h>

#include "olympus.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640


class ScreenedTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window = olympus::WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        usleep(100000); //Give the window time to create
        screen = new olympus::Screen;
        window->add_screen(screen);
    }
    
    virtual void TearDown() {
        delete screen;
        olympus::WindowManager::get_instance().destroy_all_windows();
    }
    
    olympus::Window *window;
    olympus::Screen *screen;
};

#endif