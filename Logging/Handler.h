#ifndef ETSAI_CPPUTILITIES_HANDLER_H
#define ETSAI_CPPUTILITIES_HANDLER_H

#include "CppUtilities/Logging/Level.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Abstract class defining the functionality for the log handlers.  The log handler 
 * processes the messages logged by the code and can have their own separate 
 * logging level from its Logger owner.
 * @author etsai
 */
class Handler {
public:
    /**
     * Overloaded class destructor
     * @see close
     */
    virtual ~Handler() {}

    /**
     * Publish the messages from the logger.  The boolean return type is used 
     * as a way to filter handlers without using an if statement
     * @param   msg     Message to publish
     * @return Always returns true
     */
    virtual bool publish(const string &msg)= 0;
    /**
     * Close the handler and deallocated resources
     */
    virtual void close()= 0;
    /**
     * Set the logging level for the handler
     * @param   newLevel   Logging level to set
     */
    void setLevel(Level::LevelEnums newLevel) { level= newLevel; }

    /**
     * Get the logging level for the handler
     * @return Log level
     */
    Level::LevelEnums getLevel() const { return level; }

protected:
    /**
     * Constructs a Handler with the specified level
     * @param   level   Logging level of the object
     */
    Handler(Level::LevelEnums level) { this->level= level; }

    Level::LevelEnums level;    ///< Logging level of the handler
};

}   //namespace cpputilities
}   //namespace etsai

#endif 
