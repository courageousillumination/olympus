#ifndef OLYMPUS__DEBUG__APPENDER
#define OLYMPUS__DEBUG__APPENDER
namespace olympus {
    namespace Logger {
        enum LogLevel : unsigned char;
    }
    class Appender {
    public:
        virtual ~Appender() { }
        
        /**
         * This will do the actual heavy lifting of the appender and
         * do all appends.
         */
        virtual void append(Logger::LogLevel level, const char *format_string, ...) = 0;
        
        /**
         * This should force evrything to shutdown
         */
        virtual void shutdown() = 0;
        
        /**
         * This should force a flush but allow continued input
         */
        virtual void flush() = 0;
    };
}
#endif
