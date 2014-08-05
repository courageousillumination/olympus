#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/logger.hpp"

#define TEST_MESSAGE "This is a test"
#define TEST_MESSAGE1 "This is a test1"
#define TEST_MESSAGE2 "This is a test2"
#define TEST_MESSAGE3 "This is a test3"
#define TEST_MESSAGE4 "This is a test4"

using namespace olympus;


std::string generate_temp_file() {
    return std::string();
}

class TestingAppender : public Appender {
public:
    void set_output(const char *output) { }
    
    void append(const char *format_string, ...) { }
        
    void shutdown() { }
   
    void flush() { }
    
    void clear() { }
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

bool appender_contains_message(TestingAppender *appender, std::string message) {
    return false;
}

TEST_F (LoggerTest, LoggerWithDefaultAppender) {
    std::string temp_file_name = generate_temp_file();
    
    Logger::get_appender()->set_output(generate_temp_file().c_str());
    Logger::set_level(Logger::DEBUG);
    LOG(Logger::DEBUG, TEST_MESSAGE);
    Logger::shutdown();
    
    //Now we need to check the file
    std::ifstream infile(temp_file_name);
    std::string line;
    infile >> line;
    
    EXPECT_EQ(std::string(TEST_MESSAGE), line);
}

TEST_F (LoggerTest, LoggerWithCustomAppender) {
    LOG(Logger::DEBUG, TEST_MESSAGE);
    appender->flush();
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE)));
}

TEST_F (LoggerTest, LoggerLevels) {
    Logger::set_level(Logger::DEBUG);
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::ERROR, TEST_MESSAGE3);
    LOG(Logger::WARN, TEST_MESSAGE4);
    
    appender->flush();
    
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE1)));
    EXPECT_FALSE(appender_contains_message(appender, std::string(TEST_MESSAGE2)));
    EXPECT_FALSE(appender_contains_message(appender, std::string(TEST_MESSAGE3)));
    EXPECT_FALSE(appender_contains_message(appender, std::string(TEST_MESSAGE4)));
    
    appender->clear();
    
    Logger::set_level(Logger::DEBUG | Logger::INFO);
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::ERROR, TEST_MESSAGE3);
    LOG(Logger::WARN, TEST_MESSAGE4);
    
    appender->flush();
    
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE1)));
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE2)));
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE3)));
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE4)));
    
    appender->clear();
    
    Logger::set_level(Logger::DEBUG | Logger::ERROR);
    
    LOG(Logger::DEBUG, TEST_MESSAGE1);
    LOG(Logger::INFO, TEST_MESSAGE2);
    LOG(Logger::ERROR, TEST_MESSAGE3);
    LOG(Logger::WARN, TEST_MESSAGE4);
    
    appender->flush();
    
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE1)));
    EXPECT_FALSE(appender_contains_message(appender, std::string(TEST_MESSAGE2)));
    EXPECT_FALSE(appender_contains_message(appender, std::string(TEST_MESSAGE3)));
    EXPECT_TRUE(appender_contains_message(appender, std::string(TEST_MESSAGE4)));
 
}
