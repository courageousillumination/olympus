#include <gtest/gtest.h>

#include "olympus.hpp"
#include "window/window.hpp"
#include "utils/shortcuts.hpp"

#include "../render/utils.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640
#define MODIFIED_HEIGHT 100
#define MODIFIED_WIDTH 100

using namespace olympus;

class WindowTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        window = WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
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

TEST_F(WindowTest, WindowShouldClose) {
    EXPECT_EQ(window->should_close(), false);
    window->set_should_close(true);
    EXPECT_EQ(window->should_close(), true);
}

TEST_F(WindowTest, WindowWithScreen) {
    EasyScreen *screen = create_easy_screen();
    window->add_screen(screen->screen);
    
    //Create a new square that covers the entire screen
    Renderable *r = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 1.0, 0.0, 0.0);
    screen->world->add_child(r);
    
    window->render();
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
    destroy_square(r);
    destroy_easy_screen(screen);
}