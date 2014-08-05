#ifndef OLYMPUS__DEBUG__STREAM_APPENDER
#define OLYMPUS__DEBUG__STREAM_APPENDER

#include <iostream>

#include "debug/appender.hpp"

namespace olympus {
    class StreamAppender : public Appender {
    private:
        std::ostream &_output;
    public:
        StreamAppender(std::ostream &output);
        void append(const char *format_string, ...);
        void shutdown();
        void flush();
    };
}
#endif
