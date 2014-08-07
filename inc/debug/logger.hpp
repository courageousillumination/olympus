#ifndef OLYMPUS__DEBUG__LOGGER
#define OLYMPUS__DEBUG__LOGGER

#include <string.h>

#include "debug/appender.hpp"

#ifndef NDEBUG
#define NDEBUG 0
#endif

#define FILE_SHORT (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace olympus {  
    namespace Logger {
        enum LogLevel : unsigned char {
            DEBUG = 0b100,
            INFO  = 0b011,
            WARN  = 0b010,
            ERROR = 0b001,
            NONE  = 0b000
        };  
        
        bool at_level(LogLevel level);
        const char *level_to_string(LogLevel level);
        
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
            olympus::Logger::get_appender()->append(level, "%s:%d:%s(): " fmt,\
                            FILE_SHORT, __LINE__, __func__, ##__VA_ARGS__); }\
        } while (0)
                                
#endif
