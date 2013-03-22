#ifndef ETSAI_CPPUTILITIES_INVALIDARGUMENTEXCEPTION
#define ETSAI_CPPUTILITIES_INVALIDARGUMENTEXCEPTION

#include "CppUtilities/Core/CppUtilitiesException.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Indicates an invalid argument was passed into a function
 * @author etsai
 */
class InvalidArgumentException : public CppUtilitiesException {
public:
    /**
     * Constructs an InvalidArgumentException 
     * this library should have their own exception type
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    InvalidArgumentException(const string& msg, const string& function, int lineNo, int status) : 
            CppUtilitiesException("FileException", msg, function, lineNo, status) {
    }
};

}   //namespace cpputilities
}   //namespace etsai

#endif
