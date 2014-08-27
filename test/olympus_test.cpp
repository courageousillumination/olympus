#include <gtest/gtest.h>

#include "olympus.hpp"
#include "common/olympus_environment.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new OlympusEnvironment);
    return RUN_ALL_TESTS();
}