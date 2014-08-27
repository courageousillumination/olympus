#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdarg.h>

#include "test_appender.hpp"

using namespace olympus;

void TestAppender::append(Logger::LogLevel level, const char *format_string, ...) {
    //Append
    char buff[2048];
    va_list args;
    va_start(args, format_string);
    vsprintf(buff, format_string, args);
    va_end(args);
    _output.push_back(std::string(buff));
    
    //If this happened something went wrong. Throw an exception.
    if (!_expect_error && level == Logger::ERROR) {
        std::cout << buff << '\n';
        throw std::runtime_error("Logged an error message when I wasn't expecting one.");
    }
    
}
void TestAppender::shutdown() { }
void TestAppender::flush() { }
void TestAppender::clear() { 
    _output.clear();
}

void TestAppender::set_expect_error(bool flag) {
    _expect_error = flag;
}

bool TestAppender::contains_string(std::string string) {
    for (unsigned i = 0; i < _output.size(); i++) {
        std::size_t found = _output[i].find(": ");
        std::string substring = _output[i].substr(found + 2, std::string::npos);
        if (substring == string) {
            return true;
        }
    }
    return false;
}