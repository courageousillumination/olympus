#include <exception>
#include <stdexcept>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "common/olympus_environment.hpp"
#include "window/window_manager.hpp"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

using namespace olympus;

/// The following are used to test keyboard input
static unsigned COUNTER = 0;
static unsigned COUNTER1 = 0;
static unsigned COUNTER2 = 0;
static void test_keyboard_handler(Window *window, int key, int scancode, int actions, int mods) {
     COUNTER++;
}
static void test_keyboard_handler1(Window * window, int key, int scancode, int actions, int mods) {
     COUNTER1++;
}
static void test_keyboard_handler2(Window * window, int key, int scancode, int actions, int mods) {
     COUNTER2++;
}

class WindowManagerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    
    virtual void TearDown() {
        WindowManager::get_instance().destroy_all_windows();
    }
};

TEST_F (WindowManagerTest, WindowManagerWindowCreation) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    ASSERT_TRUE(window != nullptr);
    EXPECT_EQ(window->get_width(), DEFAULT_WIDTH);
    EXPECT_EQ(window->get_height(), DEFAULT_HEIGHT);
}


TEST_F (WindowManagerTest, WindowManagerWindowDestructionSingle) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    ASSERT_TRUE(window != nullptr);
    window_manager.destroy_window(window);
    window_manager.destroy_window(nullptr);
}

TEST_F (WindowManagerTest, FailsToCreateWindow) {
    get_test_appender()->set_expect_error(true);
    
    WindowManager::get_instance().destroy_backend();
    try {
        WindowManager::get_instance().create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
        EXPECT_TRUE(false); //fail
    } catch (std::runtime_error e) {
        EXPECT_STREQ("Failed to create GLFW window", e.what());
    } catch (...) {
        EXPECT_TRUE(false); //fail
    }
    //Re initalize the backend since everyone else expects it to exst.
    WindowManager::get_instance().initialize_backend();
    get_test_appender()->set_expect_error(false);
}


TEST_F (WindowManagerTest, WindowManagerWindowDestructionAll) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    ASSERT_TRUE(window != nullptr);
    window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(window_manager.get_num_windows(), 3);
    window_manager.destroy_all_windows();
    EXPECT_EQ(window_manager.get_num_windows(), 0);
}

/**
 * This is put on the window manager because it is the centeral point for all input.
 */
TEST_F(WindowManagerTest, WindowManagerHandleKeyboardInput) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(COUNTER, 0);
    
    //We attach to this window a keyboard button handler
    window->set_keyboard_callback(test_keyboard_handler);
    //Now we have to simulate a keyboard press.
    window_manager.simulate_keypress(window, 0, 0, 0, 0);
    //Finally we need to poll to make sure that we process the input
    window_manager.poll();
    
    EXPECT_EQ(COUNTER, 1);
   
}

TEST_F(WindowManagerTest, WindowManagerHandleKeyboardInputMultiple) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window1 = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    Window *window2 = window_manager.create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(COUNTER1, 0);
    EXPECT_EQ(COUNTER2, 0);
    
    window1->set_keyboard_callback(test_keyboard_handler1);
    window2->set_keyboard_callback(test_keyboard_handler2);
    
    window_manager.simulate_keypress(nullptr, 0, 0, 0, 0);
    window_manager.simulate_keypress(window1, 0, 0, 0, 0);
    window_manager.simulate_keypress(window2, 0, 0, 0, 0);
    
    window_manager.poll();
    
    EXPECT_EQ(COUNTER1, 1);
    EXPECT_EQ(COUNTER2, 1);
}