#ifndef OLYMPUS__DEBUG__LOGGER
#define OLYMPUS__DEBUG__LOGGER

#ifndef NDEBUG
#define NDEBUG 0
#endif

#include "debug/appender.hpp"

namespace olympus {  
    namespace Logger {
        enum LogLevel {
            DEBUG = 0b100,
            INFO  = 0b011,
            WARN  = 0b010,
            ERROR = 0b001,
            NONE  = 0b000
        };  
        
        bool at_level(LogLevel level);
        
        Appender *get_appender();
        LogLevel get_level();
        
        void set_appender(Appender *appender);
        void set_level(LogLevel level);
        void set_level(int level);
        /**
         * This will mainly shutdown any appenders on this logger
         */
        void shutdown();
    }
};

///This macro was taken from 
//http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing
#define LOG(level, fmt, ...) \
        do { if (!NDEBUG && olympus::Logger::get_appender() != nullptr &&\
                  olympus::Logger::at_level(level)) { \
            olympus::Logger::get_appender()->append("%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__,##__VA_ARGS__); }\
        } while (0)
                                
#endif
