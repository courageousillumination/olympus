#include "debug/appender.hpp"
#include "debug/logger.hpp"

using namespace olympus;
using namespace olympus::Logger;

Appender::Appender(int level) {
    _level = (LogLevel) level;
}

bool Appender::at_level(LogLevel level) {
    if (level == DEBUG) { 
        return ((_level & DEBUG) != 0);
    }
    return (_level & 0b11) >= level;
}

void Appender::set_level(Logger::LogLevel level) {
    _level = level;
}

void Appender::set_level(int level) {
    _level = (LogLevel) level;
}

LogLevel Appender::get_level() {
    return _level;
}