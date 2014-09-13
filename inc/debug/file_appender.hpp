#ifndef OLYMPUS__DEBUG__FILE_APPENDER
#define OLYMPUS__DEBUG__FILE_APPENDER

#include <stdio.h>

#include "debug/appender.hpp"

namespace olympus {
    /**
     * This appender writes to a specified file. It will open and close the file
     * taking full ownership.
     */
    class FileAppender : public Appender {
    private:
        FILE *_output;
    public:
        
        FileAppender(int level, const char *output);
        void append(Logger::LogLevel level, const char *format_string, ...);
        void shutdown();
        void flush();
    };
}
#endif
