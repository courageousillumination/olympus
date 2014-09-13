#include "debug/logger.hpp"

#include "debug/file_appender.hpp"

using namespace olympus;
using namespace olympus::Logger;

static std::vector<Appender*> _appenders;

const std::vector<Appender *> &olympus::Logger::get_appenders() {
    return _appenders;
}
        
void olympus::Logger::add_appender(Appender *appender) {
    _appenders.push_back(appender);
}

void olympus::Logger::remove_appender(Appender *appender) {
    for(std::vector<Appender *>::iterator it = _appenders.begin();
        it != _appenders.end(); it++) {
        if ((*it) == appender) {
            _appenders.erase(it);
            return;
        }
    }
}

void olympus::Logger::shutdown() {
    for (auto appender : _appenders) {
        appender->shutdown();
    }
}

const char *olympus::Logger::level_to_string(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        default:
            return "Unsupported logging level";
    }
}