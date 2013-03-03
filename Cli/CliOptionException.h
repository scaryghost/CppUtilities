#ifndef ETSAI_CPPUTILITIES_CLIOPTIONEXCEPTION
#define ETSAI_CPPUTILITIES_CLIOPTIONEXCEPTION

#include "CppUtilities/Core/CppUtilitiesException.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Indicates an error with a command line option.
 * @author etsai
 */
class CliOptionException : public CppUtilitiesException {
public:
    /**
     * Constructs a CliOptionException 
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    CliOptionException(const string& msg, const string& function, int lineNo, int status) : 
            CppUtilitiesException("CliOptionException", msg, function, lineNo, status) {
    }
};

}   //namespace cpputilities
}   //namespace etsai

#endif
