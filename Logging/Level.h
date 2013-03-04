#ifndef ETSAI_CPPUTILITIES_LEVEL_H
#define ETSAI_CPPUTILITIES_LEVEL_H

namespace etsai {
namespace cpputilities {

/**
 * Logging levels that set how much detail is captured 
 * by the logging utilities
 */
enum Level {
    ALL,        ///< All messages should be logged
    FINEST,     ///< Provides the most detailed tracing
    FINER,      ///< Provides more detailed tracing
    FINE,       ///< Provides some tracing
    CONFIG,     ///< Configuration messages
    INFO,       ///< Informational messages
    WARNING,    ///< Indicates potential problems
    SEVERE      ///< Serious problem or failure 
};

}   //namespace cpputilities
}   //namespace etsai

#endif
