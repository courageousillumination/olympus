#ifndef OLYMPUS_TEST__TEST_APPENDER
#define OLYMPUS_TEST__TEST_APPENDER

#include <vector>

#include "debug/appender.hpp"
#include "debug/logger.hpp"
/**
 * This class is a simple in memory appender used by the testing framework.
 * It will throw an exception on any errors it receives and has capacity to
 * check if a message is present.
 */
class TestAppender : public olympus::Appender {
private:
    bool _expect_error, _expect_warning;
    std::vector<std::string> _output;
public:
    
    void append(olympus::Logger::LogLevel level, const char *format_string, ...);
    void shutdown();
    void flush();
    void clear();
    
    //If we expect an error we can set this flag. It ought to be cleared at the end
    //of the test.
    void set_expect_error(bool flag);
    void set_expect_warning(bool flag);
    
    bool contains_string(std::string string);
};
#endif