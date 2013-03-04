#ifndef ETSAI_CPPUTILITIES_FILEEXCEPTION
#define ETSAI_CPPUTILITIES_FILEEXCEPTION

#include "CppUtilities/Core/CppUtilitiesException.h"

#include <string>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Indicates an error processing a file
 * @author etsai
 */
class FileException : public CppUtilitiesException {
public:
    /**
     * Constructs a FileException 
     * this library should have their own exception type
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    FileException(const string& msg, const string& function, int lineNo, int status) : 
            CppUtilitiesException("FileException", msg, function, lineNo, status) {
    }
};

}   //namespace cpputilities
}   //namespace etsai

#endif
