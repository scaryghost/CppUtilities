#include "CppUtilities/Logging/Logger.h"

#include <cstdio>
#include <mutex>
#include <stdarg.h>

namespace etsai {
namespace cpputilities {

using std::lock_guard;
using std::make_pair;
using std::mutex;
using std::vsnprintf;

unordered_map<string, Logger> Logger::loggers;
static mutex loggerMutex;

Logger* Logger::getLogger(const string &loggerName) {
    lock_guard<mutex> lock(loggerMutex);
    if (!loggers.count(loggerName)) {
        loggers.insert(make_pair(loggerName, Logger()));
    }
    return &loggers.at(loggerName);
}

Logger::Logger() :
    level(Level::CONFIG) {
}

void Logger::addHandler(Handler *handler) {
    handlers.insert(handler);
}

void Logger::removeHandler(Handler *handler) {
    handlers.erase(handler);
}

void Logger::removeAllHandlers() {
    handlers.clear();
}

void Logger::setLevel(Level::LevelEnums newLevel) {
    level= newLevel;
}

void Logger::log(Level::LevelEnums level, const string &format, ...) {
    va_list args;
    auto publish= [this, &level](const string& msg) -> bool {
        for(auto it= handlers.begin(); it != handlers.end(); it++) {
            level >= (*it)->getLevel() && (*it)->publish(msg);
        }
        return true;
    };
    
    char buffer[256];
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format.c_str(), args);
    (level >= this->level) && publish(buffer);
}

const unordered_set<Handler*>& Logger::getHandlers() const {
    return handlers;
}

Level::LevelEnums Logger::getLevel() const {
    return level;
}

}
}
