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
        //All other tests need the logger to be in a proper state 
        default_level = Logger::get_level();
        old = Logger::get_appender();
        
        stream = new std::stringstream;
        appender = new StreamAppender(*stream);
        Logger::set_appender(appender);
        Logger::set_level(Logger::DEBUG | Logger::INFO);
    }
    
    virtual void TearDown() {
        appender->shutdown();
        delete appender;
        delete stream;
        
        Logger::set_level(default_level);
        Logger::set_appender(old);
    }
    
    StreamAppender *appender;
    std::stringstream *stream;
    
    Logger::LogLevel default_level;
    Appender *old;
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
    
    LOG(Logger::ERROR, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, "[\033[1;31m"));
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
    
    LOG(Logger::NONE, TEST_STRING1);
    appender->flush();
    EXPECT_TRUE(stream_contains_string(stream, TEST_STRING1));
}
