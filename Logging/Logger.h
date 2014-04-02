#ifndef ETSAI_CPPUTILITIES_LOGGER
#define ETSAI_CPPUTILITIES_LOGGER

#include "Handler.h"
#include "Level.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace etsai {
namespace cpputilities {

using std::string;
using std::unordered_map;
using std::unordered_set;

/**
 * Logs messages, filtered by level.  The messages are passed through each log handler
 * @author etsai
 */
class Logger {
public:
    /**
     * Get the logger object associated with the given name.  The logger object is not dynamically allocated.
     * @param   loggerName  Name of the logger object
     * @return  Logger object of the given name
     */
    static Logger* getLogger(const string &loggerName);

    /**
     * Add a handler.  Users are expected to free any resources from the Handler object
     * @param   handler     Desired handler to pair with the logger
     */
    void addHandler(Handler *handler);
    /**
     * Disassociate the handler from the logger
     * @param   handler     Handler to remove
     */
    void removeHandler(Handler *handler);
    /**
     * Remove all handlers from the logger
     */
    void removeAllHandlers();
    /**
     * Sets the logging level
     * @param   newLevel    New level of the logger
     */
    void setLevel(Level::LevelEnums newLevel);
    /**
     * Log a message of the specified level, up to 255 characters.  If a message's log level is below the set level, 
     * the message will not be passed on to the handlers
     * @param   level   The message's log level
     * @param   format  The printf format for the log message
     * @param   ...     Argument list for the format substitution
     */
    void log(Level::LevelEnums level, const string &format, ...);

    /**
     * Get a reference to the handlers associated with the logger
     * @return Reference to a set of handlers
     */
    const unordered_set<Handler*>& getHandlers() const;
    /**
     * Get the log level of the logger
     * @return Logging level
     */
    Level::LevelEnums getLevel() const;

private:
    Level::LevelEnums level;                                ///< Logging level of the logger
    unordered_set<Handler*> handlers;           ///< List of handlers tied to the logger

    /**
     * Constructs a logger with log level set to INFO.
     * Constructor is private so users must use the getLogger function
     */
    Logger();

    static unordered_map<string, Logger> loggers;     ///< Map of all loggers created
};  //class Logger

}   //namespace cpputilities
}   //namespace etsai

#endif 
