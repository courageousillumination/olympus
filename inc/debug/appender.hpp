#ifndef OLYMPUS__DEBUG__APPENDER
#define OLYMPUS__DEBUG__APPENDER
namespace olympus {
    class Appender {
    public:
        virtual ~Appender() { }
        /**
         * Takes a single string to set the output stream, there may
         * be a better way of handeling output setting than this
         */
        virtual void set_output(const char *output) { }
        
        /**
         * This will do the actual heavy lifting of the appender and
         * do all appends.
         */
        virtual void append(const char *format_string, ...) = 0;
        
        /**
         * This should force evrything to shutdown
         */
        virtual void shutdown() { }
        
        /**
         * This should force a flush but allow contiued input
         */
        virtual void flush() { }
    };
};
#endif
