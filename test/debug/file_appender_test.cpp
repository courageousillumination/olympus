#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "debug/logger.hpp"
#include "debug/file_appender.hpp"

#define TEST_FILE "/tmp/olympus_log.tmp"
#define TEST_STRING "This is a test"

using namespace olympus;

class FileAppenderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        appender = new FileAppender;
        appender->set_output(TEST_FILE);
        Logger::set_appender(appender);
        Logger::set_level(Logger::DEBUG);
    }
    
    virtual void TearDown() {
        //Make sure we always shutdown
        Logger::shutdown();
        delete appender;
    }
    
    FileAppender *appender;
};


bool log_file_contains_string(const char *file_name, std::string string) {
    std::ifstream fin(file_name);
    bool result = false;
    
    for(std::string line; getline(fin, line);) {
        std::size_t found = line.find(":");
        std::string substring = line.substr(found + 2, std::string::npos);
        if (substring == string) {
            result = true;
        }
    }
    
    fin.close();
    return result;
}

TEST_F (FileAppenderTest, FileAppender) {
    LOG(Logger::DEBUG, TEST_STRING);
    appender->flush();
    EXPECT_TRUE(log_file_contains_string(TEST_FILE, TEST_STRING));
}
