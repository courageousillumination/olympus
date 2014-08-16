#include <gtest/gtest.h>

#include "olympus.hpp"
#include "olympus_test.hpp"

using namespace olympus;

static TestAppender *appender = nullptr;

void OlympusEnvironment::TearDown() {
    delete appender;
}
void OlympusEnvironment::SetUp() {
    appender = new TestAppender();
    appender->set_expect_error(false);
    Logger::set_appender(appender);
    //We will only be checking the logger for warns or errors. Anything else
    // we don't need.
    Logger::set_level(Logger::WARN);
}


void logger_expect_error(bool flag) {
    appender->set_expect_error(flag);
}


bool logger_contains_string(std::string s) {
    return appender->contains_string(s);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new OlympusEnvironment);
    return RUN_ALL_TESTS();
}