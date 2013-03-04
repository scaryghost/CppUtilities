#ifndef ETSAI_CPPUTILITIES_UNKNOWNHOSTEXCEPTION
#define ETSAI_CPPUTILITIES_UNKNOWNHOSTEXCEPTION

#include "CppUtilities/Core/CppUtilitiesException.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Indicates an IP address cannot be resolved.  Based on the Java class of the same name
 * @author etsai
 */
class UnknownHostException : public CppUtilitiesException {
public:
    /**
     * Constructs an UnknownHostException 
     * this library should have their own exception type
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    UnknownHostException(const string& msg, const string& function, int lineNo, int status) : 
            CppUtilitiesException("UnknownHostException", msg, function, lineNo, status) {
    }
};

}
}

#endif
