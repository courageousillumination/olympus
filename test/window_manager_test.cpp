#include <gtest/gtest.h>
#include <iostream>

#include "olympus.hpp"
#include "window_manager.hpp"

using namespace olympus;

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
    Window *window = window_manager.create_window(640, 480);
    ASSERT_TRUE(window != nullptr);
    EXPECT_EQ(window->get_width(), 640);
    EXPECT_EQ(window->get_height(), 480);
}


TEST_F (WindowManagerTest, WindowManagerWindowDestructionSingle) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(640, 480);
    ASSERT_TRUE(window != nullptr);
    window_manager.destroy_window(window);
    window_manager.destroy_window(nullptr);
}


TEST_F (WindowManagerTest, WindowManagerWindowDestructionAll) {
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(640, 480);
    ASSERT_TRUE(window != nullptr);
    window_manager.create_window(640, 480);
    window_manager.create_window(640, 480);
    
    EXPECT_EQ(window_manager.get_num_windows(), 3);
    window_manager.destroy_all_windows();
    EXPECT_EQ(window_manager.get_num_windows(), 0);
    window_manager.destroy_all_windows();
}
