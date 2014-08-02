#include <gtest/gtest.h>

#include "olympus.hpp"
#include "window.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640
#define MODIFIED_HEIGHT 100
#define MODIFIED_WIDTH 100

using namespace olympus;

class WindowTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window =  WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }
    
    virtual void TearDown() {
        WindowManager::get_instance().destroy_all_windows();
    }
    
    Window *window;
};

TEST_F (WindowTest, WindowGettersAndSetters) {
    EXPECT_EQ(window->get_width(), DEFAULT_WIDTH);
    EXPECT_EQ(window->get_height(), DEFAULT_HEIGHT);
    
    window->set_height(MODIFIED_HEIGHT);
    window->set_width(MODIFIED_WIDTH);
    
    EXPECT_EQ(window->get_width(), MODIFIED_WIDTH);
    EXPECT_EQ(window->get_height(), MODIFIED_HEIGHT);
    
    window->set_dimensions(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(window->get_width(), DEFAULT_WIDTH);
    EXPECT_EQ(window->get_height(), DEFAULT_HEIGHT);
}