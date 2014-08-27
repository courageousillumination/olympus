#ifndef OLYMPUS_ENVIRONMENT
#define OLYMPUS_ENVIRONMENT

#include <gtest/gtest.h>

#include "olympus.hpp"

#include "test_appender.hpp"

/**
 * Global testing Environment.
 */
class OlympusEnvironment : public ::testing::Environment {
    void SetUp();
    void TearDown();
};

TestAppender *get_test_appender();

#endif