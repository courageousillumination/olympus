#include "debug/logger.hpp"

#include "debug/file_appender.hpp"

using namespace olympus;
using namespace olympus::Logger;


static Appender *_appender = new FileAppender;
static LogLevel _level;

bool olympus::Logger::at_level(LogLevel level) {
    return _level >= level;
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
}