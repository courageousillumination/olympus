#include <unistd.h>

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "olympus.hpp"
#include "window/window.hpp"
#include "utils/shortcuts.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640
#define MODIFIED_HEIGHT 100
#define MODIFIED_WIDTH 100

using namespace olympus;

class WindowTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window = WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	usleep(100000); //Give the window time to create
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
    
    EXPECT_TRUE(window->get_graphics_state() != nullptr);
}

TEST_F(WindowTest, WindowShouldClose) {
    EXPECT_EQ(window->get_should_close(), false);
    window->set_should_close(true);
    EXPECT_EQ(window->get_should_close(), true);
}

TEST_F(WindowTest, EasyWindowShortuct) {
    EasyWindow *easy_window = create_easy_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_EQ(WindowManager::get_instance().get_num_windows(), 2);
    destroy_easy_window(easy_window);
}