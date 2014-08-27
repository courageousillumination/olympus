#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include <stdarg.h>
#include <string.h>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/logger.hpp"

#include "../test_appender.hpp"

#define TEST_MESSAGE "This is a test"
#define TEST_MESSAGE1 "This is a test1"
#define TEST_MESSAGE2 "This is a test2"
#define TEST_MESSAGE3 "This is a test3"
#define TEST_MESSAGE4 "This is a test4"

using namespace olympus;

class LoggerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        default_level = Logger::get_level();
        old = Logger::get_appender();
        
        appender = new TestAppender;
        appender->set_expect_error(true);
        Logger::set_appender(appender);
        Logger::set_level(Logger::DEBUG);
    }
    
    virtual void TearDown() {
        //Make sure we always shutdown
        appender->shutdown();
        delete appender;
        
        Logger::set_level(default_level);
        Logger::set_appender(old);
    }
    
    Logger::LogLevel default_level;
    TestAppender *appender;
    Appender *old;
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
