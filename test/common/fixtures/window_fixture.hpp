#ifndef OLYMPUS__TEST__FIXTURES__WINDOW
#define OLYMPUS__TEST__FIXTURES__WINDOW

#include <unistd.h>

#include <gtest/gtest.h>

#include "olympus.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640


class WindowedTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window = olympus::WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        usleep(100000); //Give the window time to create
    }
    
    virtual void TearDown() {
        olympus::WindowManager::get_instance().destroy_all_windows();
    }
    
    olympus::Window *window;
};

#endif