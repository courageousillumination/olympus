#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/stream_appender.hpp"

#define TEST_FILE "/tmp/olympus_log.tmp"
#define TEST_STRING1 "This is a test1"
#define TEST_STRING2 "This is a test2"
#define TEST_STRING3 "This is a test3"
#define TEST_STRING4 "This is a test4"

using namespace olympus;

class StreamAppenderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        appender = new StreamAppender(stream);
        Logger::set_appender(appender);
        Logger::set_level(Logger::DEBUG);
    }
    
    virtual void TearDown() {
        //Make sure we always shutdown
        Logger::shutdown();
        delete appender;
    }
    
    StreamAppender *appender;
    std::stringstream stream;
};



bool stream_contains_string(std::istream &stream, std::string string) {
    bool result = false;
    
    for(std::string line; getline(stream, line);) {
        std::size_t found = line.find(": ");
        std::string substring = line.substr(found + 2, std::string::npos);
        if (substring == string) {
            result = true;
        }
    }
    return result;
}

TEST_F (StreamAppenderTest, StreamAppender) {
    LOG(Logger::DEBUG, TEST_STRING1);
    LOG(Logger::INFO, TEST_STRING2);
    LOG(Logger::WARN, TEST_STRING3);
    LOG(Logger::ERROR, TEST_STRING4);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING2));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING3));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING4));
}
