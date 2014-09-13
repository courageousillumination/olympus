#ifndef OLYMPUS__DEBUG__APPENDER
#define OLYMPUS__DEBUG__APPENDER
namespace olympus {
    namespace Logger {
        enum LogLevel : unsigned char;
    }
    /**
     * An appender is an abstraction around any output source for logging.
     * This could be a stream, a file, a network, etc. Anything that wants
     * to log has to inherit from this class.
     */
    class Appender {
    private:
        Logger::LogLevel _level;
    public:
        Appender(int level);
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
        
        /**
         * Returns true if the appender is listening for statements at this level.
         */
        bool at_level(Logger::LogLevel);
        
        void set_level(Logger::LogLevel level);
        void set_level(int level);
        Logger::LogLevel get_level();
    };
}
#endif
