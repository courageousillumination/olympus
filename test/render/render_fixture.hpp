#ifndef OLYMPUS__TEST__RENDER__RENDER_FIXTURE
#define OLYMPUS__TEST__RENDER__RENDER_FIXTURE

#include <gtest/gtest.h>
#include "olympus.hpp"

class RenderTest : public ::testing::Test {
protected:
    static void SetUpTestCase() {
        _window = olympus::WindowManager::get_instance().create_window(640, 480);
    }
    
    static void TearDownTestCase() {
        olympus::WindowManager::get_instance().destroy_window(_window);
        _window = nullptr;
    }
    
    static olympus::Window *_window;
};

olympus::Window *RenderTest::_window = nullptr;

#endif