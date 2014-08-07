#include <stdarg.h>

#include "debug/logger.hpp"
#include "debug/file_appender.hpp"

using namespace olympus;

FileAppender::FileAppender(const char *output) {
    _output = fopen(output, "w");
}
void FileAppender::append(Logger::LogLevel level, const char *format_string, ...) {
    fprintf(_output, "[%s] ", Logger::level_to_string(level));
    va_list args;
    va_start(args, format_string);
    vfprintf(_output, format_string, args);
    va_end(args);
    fprintf(_output, "\n");
}
void FileAppender::shutdown() { 
    fclose(_output);
}
void FileAppender::flush() {
    fflush(_output);
}