#include <iostream>
#include <sstream>
#include <fstream>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/file_appender.hpp"

#include "common/olympus_environment.hpp"

#define TEST_FILE "/tmp/olympus_log.tmp"
#define TEST_STRING1 "This is a test1"
#define TEST_STRING2 "This is a test2"
#define TEST_STRING3 "This is a test3"
#define TEST_STRING4 "This is a test4"

#define FILE_NAME "/tmp/file"

using namespace olympus;

class FileAppenderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        appender = new FileAppender(Logger::DEBUG | Logger::INFO, FILE_NAME);
        Logger::add_appender(appender);
    }
    
    virtual void TearDown() {
        Logger::remove_appender(appender);
        appender->shutdown();
        delete appender;
    }
    
    FileAppender *appender;
};



bool file_contains_string(const char *file_name, std::string string) {
    std::ifstream t(file_name);
    std::string current_stream((std::istreambuf_iterator<char>(t)),
                                std::istreambuf_iterator<char>());
    t.close();
    return current_stream.find(string) != std::string::npos;
}

TEST_F (FileAppenderTest, AllLevels) {
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
    

    LOG(Logger::INFO, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
    
    LOG(Logger::WARN, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
    
    
    get_test_appender()->set_expect_error(true);
    
    LOG(Logger::ERROR, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
    
    get_test_appender()->set_expect_error(false);
    
    LOG(Logger::NONE, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
}

TEST_F (FileAppenderTest, ChangeLevel) {
    appender->set_level(Logger::NONE);
    EXPECT_EQ(Logger::NONE, appender->get_level());
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_FALSE(file_contains_string(FILE_NAME, TEST_STRING1));
    
    appender->set_level(Logger::DEBUG | Logger::INFO);
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(file_contains_string(FILE_NAME, TEST_STRING1));
}
