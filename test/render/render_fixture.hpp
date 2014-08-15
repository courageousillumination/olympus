#ifndef OLYMPUS__TEST__RENDER__RENDER_FIXTURE
#define OLYMPUS__TEST__RENDER__RENDER_FIXTURE

#include <unistd.h>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

class RenderTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        _window = olympus::create_easy_window(640, 480);
        usleep(100000); //Give the window time to create
    }
    
    static void TearDownTestCase() {
        destroy_easy_window(_window);
        _window = nullptr;
    }
    
    static olympus::EasyWindow *_window;
};
#endif