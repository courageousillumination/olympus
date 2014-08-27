#include <gtest/gtest.h>

#include "olympus.hpp"

#define CREATE_APPENDER

#include "olympus_environment.hpp"


using namespace olympus;

static TestAppender *test_appender = nullptr;

void OlympusEnvironment::TearDown() {
    delete test_appender;
}

void OlympusEnvironment::SetUp() {
    test_appender = new TestAppender();
    test_appender->set_expect_error(false);
    Logger::set_appender(test_appender);
    // We will only be checking the logger for warns or errors. Anything else
    // we don't need and will be discarded.
    Logger::set_level(Logger::WARN);
}


TestAppender *get_test_appender() {
    return test_appender;
}