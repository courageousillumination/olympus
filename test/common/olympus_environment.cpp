#include <gtest/gtest.h>

#include "olympus.hpp"

#define CREATE_APPENDER

#include "olympus_environment.hpp"


using namespace olympus;

static TestAppender *test_appender = nullptr;

void OlympusEnvironment::TearDown() {
    // check for resource leaks
    ResourceManager::get_instance().check_allocation();
    
    Logger::shutdown();
    delete test_appender;
}

void OlympusEnvironment::SetUp() {
    // We will only be checking the logger for warns or errors. Anything else
    // we don't need and will be discarded.
    test_appender = new TestAppender(Logger::WARN);
    test_appender->set_expect_error(false);
    Logger::add_appender(test_appender);
}


TestAppender *get_test_appender() {
    return test_appender;
}