#include "debug/logger.hpp"

#include "debug/file_appender.hpp"

using namespace olympus;
using namespace olympus::Logger;


static Appender *_appender = nullptr;
static LogLevel _level = NONE;

bool olympus::Logger::at_level(LogLevel level) {
    if (level == DEBUG) { 
        return ((_level & DEBUG) != 0);
    }
    return (_level & 0b11) >= level;
}

void olympus::Logger::set_level(int level) {
    olympus::Logger::set_level((LogLevel) level);
}

Appender *olympus::Logger::get_appender() { return _appender; }
LogLevel olympus::Logger::get_level() { return _level; }

void olympus::Logger::set_appender(Appender *appender) { _appender = appender; }
void olympus::Logger::set_level(LogLevel level) { _level = level; }

void olympus::Logger::shutdown() {
    if (_appender != nullptr) {
        _appender->shutdown();
    }
    _appender = nullptr;
    _level = NONE;
}