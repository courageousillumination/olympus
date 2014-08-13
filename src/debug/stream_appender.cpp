#include <iostream>
#include <stdarg.h>

#include "debug/logger.hpp"
#include "debug/stream_appender.hpp"

using namespace olympus;

StreamAppender::StreamAppender(std::ostream  & output) : _output(output) { }

void StreamAppender::append(Logger::LogLevel level, const char *format_string, ...) {
    char buff[2048]; //Hopefully we don't get too long of a string...
    va_list args;
    va_start(args, format_string);
    vsprintf(buff, format_string, args);
    va_end(args);
    
    switch (level) {
        case Logger::DEBUG:
            _output << "[\033[1;37mDEBUG\033[0m] ";
            break;
        case Logger::INFO:
            _output << "[\033[1;32mINFO\033[0m] ";
            break;
        case Logger::WARN:
            _output << "[\033[1;33mWARN\033[0m] ";
            break;
        case Logger::ERROR:
            _output << "[\033[1;31mERROR\033[0m] ";
            break;
        default:
            _output << "[UNKNOWN LOG LEVEL] ";
            break;
    }
    _output << buff << std::endl;
}
void StreamAppender::shutdown() {
    //Someone else is responsible for tearing down the stream
}
void StreamAppender::flush() {
    _output.flush();
}