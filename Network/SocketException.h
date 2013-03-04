#ifndef ETSAI_CPPUTILITIES_SOCKETEXCEPTION
#define ETSAI_CPPUTILITIES_SOCKETEXCEPTION

#include "CppUtilities/Core/CppUtilitiesException.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Indicates an error with using UDP/TCP sockets
 * @author etsai
 */
class SocketException : public CppUtilitiesException {
public:
    /**
     * Constructs a SocketException 
     * this library should have their own exception type
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    SocketException(const string& msg, const string& function, int lineNo, int status) : 
            CppUtilitiesException("SocketException", msg, function, lineNo, status) {
    }
};

}
}

#endif
