#ifndef ETSAI_CPPUTILITIES_LEVEL_H
#define ETSAI_CPPUTILITIES_LEVEL_H

#include "InvalidArgumentException.h"

#include <climits>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace etsai {
namespace cpputilities {

using std::hash;
using std::string;
using std::unordered_map;
using std::unordered_set;

/**
 * Logging levels that set how much detail is captured by the logging utilities
 * @author etsai
 */
class Level {
public:
    /** Enum values for the logging levels */
    enum LevelEnums {
        ALL= INT_MIN,        ///< All messages should be logged
        FINEST= 300,     ///< Provides the most detailed tracing
        FINER= 400,      ///< Provides more detailed tracing
        FINE= 500,       ///< Provides some tracing
        CONFIG= 700,     ///< Configuration messages
        INFO= 800,       ///< Informational messages
        WARNING= 900,    ///< Indicates potential problems
        SEVERE= 1000      ///< Serious problem or failure 
    };

    static LevelEnums parse(const string& name) throw(InvalidArgumentException);
    static LevelEnums parse(int value);
    static const unordered_set<LevelEnums, hash<int>>& values();

private:
    static unordered_map<string, LevelEnums> nameToLevel;
    static unordered_map<int, LevelEnums> valueToLevel;
    static unordered_set<LevelEnums,hash<int> > allLevelValues;
};

}   //namespace cpputilities
}   //namespace etsai

#endif
