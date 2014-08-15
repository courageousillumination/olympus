#include <gtest/gtest.h>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

using namespace olympus;

TEST (ShortcutsTest, TestEasyWindow) {
    EasyWindow *window = create_easy_window(640, 480);
    destroy_easy_window(window);
}