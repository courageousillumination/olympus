#ifndef OLYMPUS__DEBUG__LOGGER
#define OLYMPUS__DEBUG__LOGGER

#include <vector>

#include <string.h>

#include "debug/appender.hpp"

#ifndef NDEBUG
#define NDEBUG 0
#endif

#define FILE_SHORT (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace olympus {
    /**
     * The Logger namespace basically acts as a wrapper around a set of appenders, with
     * a couple of macros to make logging easier.
     */
    namespace Logger {
        enum LogLevel : unsigned char {
            DEBUG = 0b100,
            INFO  = 0b011,
            WARN  = 0b010,
            ERROR = 0b001,
            NONE  = 0b000
        };
        /**
         * Converts a LogLevel to a string for better printing
         */
        const char *level_to_string(LogLevel level);
        
        /**
         * This should be called as one of the last things in the program.
         * It will shutdown any appenders still attached to the logger.
         */
        void shutdown();
        
        const std::vector<Appender *> &get_appenders();
        
        void add_appender(olympus::Appender *appender);
        void remove_appender(Appender *appender);
    }
};

///This macro was adpated from
//http://stackoverflow.com/questions/1644868/c-define-macro-for-debug-printing
#define LOG(level, fmt, ...)                                                \
        do {                                                                \
            if (!NDEBUG) {                                                  \
                for (auto appender : olympus::Logger::get_appenders()) {    \
                    if (appender->at_level(level)) {                        \
                        appender->append(level, "%s:%d:%s(): " fmt,         \
                            FILE_SHORT, __LINE__, __func__, ##__VA_ARGS__); \
                    }                                                       \
                }                                                           \
            }                                                               \
        } while (0)         
#endif
