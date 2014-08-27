#include <unistd.h>

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

#include "olympus.hpp"
#include "window/window.hpp"
#include "utils/shortcuts.hpp"

#include "common/square.hpp"
#include "common/test_block.hpp"

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640
#define MODIFIED_HEIGHT 100
#define MODIFIED_WIDTH 100

using namespace olympus;

class ScreenTest : public ::testing::Test {
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


TEST_F(ScreenTest, SingleScreen) {
    EasyScreen *screen = create_easy_screen();
    window->add_screen(screen->screen);
    
    //Create a new square that covers the entire screen
    Renderable *g = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    screen->world->add_child(g);
    
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    destroy_square(g);
    destroy_easy_screen(screen);
}

TEST_F(ScreenTest, MultipleScreens) {
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
    
    EXPECT_FALSE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 0.0, 0.0));
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
    EXPECT_TRUE(expect_color_block(DEFAULT_WIDTH / 2, 0, DEFAULT_WIDTH / 2, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    //Set a world and make sure two screens can look at the same world
    screen1->screen->set_world(screen2->world);
    
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