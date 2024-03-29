#include <iostream>
#include <stdarg.h>

#include "debug/logger.hpp"
#include "debug/stream_appender.hpp"

using namespace olympus;

StreamAppender::StreamAppender(int level, std::ostream  & output) : 
    Appender(level), _output(output) { }

void StreamAppender::append(Logger::LogLevel level, const char *format_string, ...) {
    char buff[2048]; //Hopefully we don't get too long of a string...
    va_list args;
    va_start(args, format_string);
    vsprintf(buff, format_string, args);
    va_end(args);
    
    switch (level) {
        case Logger::DEBUG:
            _output << "[\033[1;37m";
            break;
        case Logger::INFO:
            _output << "[\033[1;32m";
            break;
        case Logger::WARN:
            _output << "[\033[1;33m";
            break;
        case Logger::ERROR:
            _output << "[\033[1;31m";
            break;
        case Logger::NONE:
            _output << "[";
    }
    _output << Logger::level_to_string(level) << "\033[0m] " << buff << std::endl;
}
void StreamAppender::shutdown() {
    //Someone else is responsible for tearing down the stream
}
void StreamAppender::flush() {
    _output.flush();
}