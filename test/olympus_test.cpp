#include <gtest/gtest.h>

#include "olympus.hpp"

TEST (OlympusTest, Foo) {
    EXPECT_EQ(5, olympus::foo(2, 3));
    EXPECT_EQ(10, olympus::foo(7, 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}