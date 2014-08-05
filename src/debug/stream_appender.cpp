#include <stdarg.h>

#include "debug/stream_appender.hpp"

using namespace olympus;

StreamAppender::StreamAppender(std::ostream  & output) : _output(output) { }

void StreamAppender::append(const char *format_string, ...) {
    char buff[2048]; //Hopefully we don't get too long of a string...
    va_list args;
    va_start(args, format_string);
    vsprintf(buff, format_string, args);
    va_end(args);
    
    _output << buff << '\n';
}
void StreamAppender::shutdown() {
    //Someone else is responsible for tearing down the stream
}
void StreamAppender::flush() {
    _output.flush();
}