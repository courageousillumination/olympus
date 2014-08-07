#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <stdarg.h>
#include <string.h>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/logger.hpp"

#define TEST_MESSAGE "This is a test"
#define TEST_MESSAGE1 "This is a test1"
#define TEST_MESSAGE2 "This is a test2"
#define TEST_MESSAGE3 "This is a test3"
#define TEST_MESSAGE4 "This is a test4"

using namespace olympus;

class TestingAppender : public Appender {
private:
    std::vector<std::string> _output;
public:
    
    void append(Logger::LogLevel level, const char *format_string, ...) {
        //Repackage the varargs
        char buff[2048];
        va_list args;
        va_start(args, format_string);
        vsprintf(buff, format_string, args);
        va_end(args);
        
        _output.push_back(std::string(buff));
    }
        
    void shutdown() { }
   
    void flush() { }
    
    void clear() { 
        _output.clear();
    }
    
    bool contains_string(std::string string) {
        for (unsigned i = 0; i < _output.size(); i++) {
            std::size_t found = _output[i].find(": ");
            std::string substring = _output[i].substr(found + 2, std::string::npos);
            if (substring == string) {
                return true;
            }
        }
        return false;
    }
   
    void print() {
        for (unsigned i = 0; i < _output.size(); i++) {
            std::cout << _output[i] << '\n';
        }
    }
};

class LoggerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        appender = new TestingAppender;
        Logger::set_appender(appender);
        Logger::set_level(Logger::DEBUG);
    }
    
    virtual void TearDown() {
        //Make sure we always shutdown
        Logger::shutdown();
        delete appender;
    }
    
    TestingAppender *appender;
};

TEST_F (LoggerTest, LoggerWithCustomAppender) {
    LOG(Logger::DEBUG, TEST_MESSAGE);
    appender->flush();
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE)));
}

TEST_F (LoggerTest, LoggerLevels) {
    Logger::set_level(Logger::DEBUG);
    EXPECT_EQ(Logger::get_level(), Logger::DEBUG);
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::WARN, TEST_MESSAGE3);
    LOG(Logger::ERROR, TEST_MESSAGE4);
    
    appender->flush();
    
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE1)));
    EXPECT_FALSE(appender->contains_string(std::string(TEST_MESSAGE2)));
    EXPECT_FALSE(appender->contains_string(std::string(TEST_MESSAGE3)));
    EXPECT_FALSE(appender->contains_string(std::string(TEST_MESSAGE4)));
    
    appender->clear();
    
    Logger::set_level(Logger::DEBUG | Logger::INFO);
    EXPECT_EQ(Logger::get_level(), Logger::DEBUG | Logger::INFO);
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::WARN, TEST_MESSAGE3);
    LOG(Logger::ERROR, TEST_MESSAGE4);
    
    appender->flush();
    
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE1)));
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE2)));
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE3)));
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE4)));
    
    appender->clear();
    
    Logger::set_level(Logger::DEBUG | Logger::ERROR);
    EXPECT_EQ(Logger::get_level(), Logger::DEBUG | Logger::ERROR);
   
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::WARN, TEST_MESSAGE3);
    LOG(Logger::ERROR, TEST_MESSAGE4);
   
    appender->flush();
    
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE1)));
    EXPECT_FALSE(appender->contains_string(std::string(TEST_MESSAGE2)));
    EXPECT_FALSE(appender->contains_string(std::string(TEST_MESSAGE3)));
    EXPECT_TRUE(appender->contains_string(std::string(TEST_MESSAGE4)));
    
}
