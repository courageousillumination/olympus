#ifndef OLYMPUS__DEBUG__STREAM_APPENDER
#define OLYMPUS__DEBUG__STREAM_APPENDER

#include <iostream>

#include "debug/appender.hpp"

namespace olympus {
    /**
     * This appender can output to any standard c++ stream. This includes
     * file streams, cout/cerr, etc. It does not take ownership of the stream
     * so it the responsibility of the caller to destroy the stream.
     */
    class StreamAppender : public Appender {
    private:
        std::ostream &_output;
    public:
        StreamAppender(int level, std::ostream &output);
        void append(Logger::LogLevel level, const char *format_string, ...);
        void shutdown();
        void flush();
    };
}
#endif
