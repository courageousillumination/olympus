#include "debug/file_appender.hpp"

using namespace olympus;

void FileAppender::set_output(const char *output) {
    _output = fopen(output, "w");
}
void FileAppender::append(const char *format_string, ...) {
    fprintf(_output, "Testing");
}
void FileAppender::shutdown() { 
    fclose(_output);
}
void FileAppender::flush() {
    fflush(_output);
}