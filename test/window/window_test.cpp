#include <unistd.h>

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

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
    Renderable *g = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    screen->world->add_child(g);
    
    window->render();
    window->render();

    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    destroy_square(g);
    destroy_easy_screen(screen);
}

TEST_F(WindowTest, WindowWithMultipleScreens) {
    EasyScreen *screen1 = create_easy_screen();
    EasyScreen *screen2 = create_easy_screen();
    window->add_screen(screen1->screen, -1.0, -1.0, 1.0, 2.0);
    window->add_screen(screen2->screen, 0.0, -1.0, 1.0, 2.0);
    
    //Create a new square that covers each virtual screen
    Renderable *r = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 1.0, 0.0, 0.0);
    screen1->world->add_child(r);
    Renderable *b = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    screen2->world->add_child(b);
    
    window->render();
    window->render();
    
    EXPECT_FALSE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 0.0, 0.0));
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
    EXPECT_TRUE(expect_color_block(DEFAULT_WIDTH / 2, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    //Set a world and make sure two screens can look at the same world
    screen1->screen->set_world(screen2->world);
    
    window->render();
    window->render();

    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    //Test screen removal
    window->remove_screen(screen2->screen);
    window->render();
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    EXPECT_TRUE(expect_color_block(DEFAULT_WIDTH / 2, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 0.0, 0.0, 0.0));
    
    destroy_square(r);
    destroy_square(b);
    destroy_easy_screen(screen1);
    destroy_easy_screen(screen2);
}
