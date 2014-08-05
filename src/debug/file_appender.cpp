#include <stdarg.h>

#include "debug/file_appender.hpp"

using namespace olympus;

void FileAppender::set_output(const char *output) {
    _output = fopen(output, "w");
}
void FileAppender::append(const char *format_string, ...) {
    va_list args;
    va_start(args, format_string);
    vfprintf(_output, format_string, args);
    va_end(args);
}
void FileAppender::shutdown() { 
    fclose(_output);
}
void FileAppender::flush() {
    fflush(_output);
}