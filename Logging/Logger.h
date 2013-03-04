#ifndef ETSAI_CPPUTILITIES_LOGGER
#define ETSAI_CPPUTILITIES_LOGGER

#include "CppUtilities/Logging/Handler.h"
#include "CppUtilities/Logging/Level.h"

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
     * Get the logger object associated with the given name
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
    void setLevel(Level newLevel);
    /**
     * Log a message of the specified level.  If a message's log level is below the set level, 
     * the message will not be passed on to the handlers
     * @param   level   The message's log level
     * @param   msg     Message to log
     */
    void log(Level level, const string &msg);

    /**
     * Get a reference to the handlers associated with the logger
     * @return Reference to a set of handlers
     */
    const unordered_set<Handler*>& getHandlers() const;
    /**
     * Get the log level of the logger
     * @return Logging level
     */
    Level getLevel() const;

private:
    static unordered_map<string, Logger> loggers;     ///< Map of all loggers created

    /**
     * Constructs a logger with log level set to INFO.
     * Constructor is private so users must use the getLogger function
     */
    Logger();

    unordered_set<Handler*> handlers;     ///< List of handlers tied to the logger
    Level level;                               ///< Logging level of the logger
};  //class Logger

}   //namespace cpputilities
}   //namespace etsai

#endif 