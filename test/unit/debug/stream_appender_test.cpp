#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/stream_appender.hpp"

#include "common/olympus_environment.hpp"

#define TEST_FILE "/tmp/olympus_log.tmp"
#define TEST_STRING1 "This is a test1"
#define TEST_STRING2 "This is a test2"
#define TEST_STRING3 "This is a test3"
#define TEST_STRING4 "This is a test4"

using namespace olympus;

class StreamAppenderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        stream = new std::stringstream;
        appender = new StreamAppender(Logger::DEBUG | Logger::INFO, *stream);
        Logger::add_appender(appender);
    }
    
    virtual void TearDown() {
        Logger::remove_appender(appender);
        appender->shutdown();
        delete appender;
        delete stream;
    }
    
    StreamAppender *appender;
    std::stringstream *stream;
};



bool stream_contains_string(std::stringstream *stream, std::string string) {
    std::string current_stream = stream->str();
    return current_stream.find(string) != std::string::npos;
}

TEST_F (StreamAppenderTest, AllLevels) {
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;37m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    

    LOG(Logger::INFO, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;32m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    
    LOG(Logger::WARN, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;33m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    
    
    get_test_appender()->set_expect_error(true);
    
    LOG(Logger::ERROR, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;31m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    
    get_test_appender()->set_expect_error(false);
    
    LOG(Logger::NONE, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
}

TEST_F (StreamAppenderTest, ChangeLevel) {
    appender->set_level(Logger::NONE);
    EXPECT_EQ(Logger::NONE, appender->get_level());
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_FALSE(stream_contains_string(stream, "[\033[1;37m"));
    EXPECT_FALSE(stream_contains_string(stream, TEST_STRING1));
    
    appender->set_level(Logger::DEBUG | Logger::INFO);
    
    LOG(Logger::DEBUG, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;37m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
}
