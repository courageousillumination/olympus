#ifndef OLYMPUS__DEBUG__FILE_APPENDER
#define OLYMPUS__DEBUG__FILE_APPENDER

#include "debug/appender.hpp"

namespace olympus {
    class FileAppender : public Appender {
        /**
         * Takes in a single stream for output to a file
         */
        void set_output(const char *output);
        void append(const char *format_string, ...);
        void shutdown();
        void flush();
    };
}
#endif
