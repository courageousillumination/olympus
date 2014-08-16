#ifndef OLYMPUS_TEST__TEST_APPENDER
#define OLYMPUS_TEST__TEST_APPENDER

#include <vector>

#include "debug/appender.hpp"
#include "debug/logger.hpp"

class TestAppender : public olympus::Appender {
private:
    bool _expect_error;
    std::vector<std::string> _output;
public:
    
    void append(olympus::Logger::LogLevel level, const char *format_string, ...);
    void shutdown();
    void flush();
    void clear();
    
    //If we expect an error we can set this flag. It ought to be cleared at the end
    //of the test.
    void set_expect_error(bool flag);
    
    bool contains_string(std::string string);
};
#endif