#include "CppUtilities/Logging/Level.h"
#include "CppUtilities/Core/StatusCodes.h"

namespace etsai {
namespace cpputilities {

/**
        ALL,        ///< All messages should be logged
        FINEST,     ///< Provides the most detailed tracing
        FINER,      ///< Provides more detailed tracing
        FINE,       ///< Provides some tracing
        CONFIG,     ///< Configuration messages
        INFO,       ///< Informational messages
        WARNING,    ///< Indicates potential problems
        SEVERE
*/
unordered_map<string, Level::LevelEnums> Level::nameToLevel= {{"all", Level::ALL}, {"finest", Level::FINEST},
    {"finer", Level::FINER}, {"fine", Level::FINE}, {"config", Level::CONFIG}, {"info", Level::INFO}, 
    {"warning", Level::WARNING}, {"severe", Level::SEVERE}};

unordered_map<int, Level::LevelEnums> Level::valueToLevel= {{(int)Level::ALL, Level::ALL}, {(int)Level::FINEST, Level::FINEST}, 
    {(int)Level::FINER, Level::FINER}, {(int)Level::FINE, Level::FINE}, {(int)Level::CONFIG, Level::CONFIG}, 
    {(int)Level::INFO, Level::INFO}, {(int)Level::WARNING, Level::WARNING}, {(int)Level::SEVERE, Level::SEVERE}};

unordered_set<Level::LevelEnums, hash<int> > Level::allLevelValues= {Level::ALL,  Level::FINEST, Level::FINER, Level::FINE, Level::CONFIG, Level::INFO, 
    Level::WARNING, Level::SEVERE};

Level::LevelEnums Level::parse(const string& name) throw(InvalidArgumentException) {
    if (nameToLevel.count(name) == 0) {
        throw exception(InvalidArgumentException, "Invalid level name given: " + name, ERROR_USAGE);
    }
    return nameToLevel.find(name)->second;
}

Level::LevelEnums Level::parse(int value) {
    if (valueToLevel.count(value) == 0) {
        LevelEnums chosen(ALL);
        for(auto validValues: allLevelValues) {
            if (validValues > value) {
                return chosen;
            }
            chosen= validValues;
        }
        return chosen;
    }
    return valueToLevel.find(value)->second;

}

const unordered_set<Level::LevelEnums, hash<int>>& Level::values() {
    return allLevelValues;
}

}
}
