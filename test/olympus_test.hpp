#ifndef OLYMPUS_TEST
#define OLYMPUS_TEST

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "test_appender.hpp"

class OlympusEnvironment : public ::testing::Environment {
    void SetUp();
    void TearDown();
};

void logger_expect_error(bool flag);
bool logger_contains_string(std::string);


#endif