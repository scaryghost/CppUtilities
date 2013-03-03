#ifndef ETSAI_CPPUTILITIES_INTERNALEXCEPTION
#define ETSAI_CPPUTILITIES_INTERNALEXCEPTION

#include <exception>
#include <sstream>
#include <string>

#define exception(class, msg, status) class(msg, __FUNCTION__, __LINE__, status)

namespace etsai {
namespace cpputilities {

using std::exception;
using std::string;
using std::stringstream;

/**
 * Parent class for all CppUtilities library exceptions
 * @author etsai
 */
class CppUtilitiesException : public std::exception {
public:
    /**
     * Class destructor
     */
    ~CppUtilitiesException() throw() {
    }

    /**
     * Get the error message
     * @return Error message for the exception
     */
    const char* what() const throw() {
        return msg.c_str();
    }

    /**
     * Get the status code
     * @return Exception's status code
     */
    int getStatus() const throw() {
        return status;
    }
protected:
    /**
     * Constructs a CppUtilitiesException.  This is a protected function because all exceptions thrown by 
     * this library should have their own exception type
     * @param   msg         Error message
     * @param   function    Function name the exception was thrown at
     * @param   lineNo      Line nuimber the exception was thrown at
     * @param   status      Status code to associate with the exception
     */
    CppUtilitiesException(const string& exceptionType, const string& msg, const string& function, int lineNo, int status) {
        stringstream formattedMsg;

        formattedMsg << exceptionType << " - " << msg << " (in " << function << " line " << lineNo << ")";
        this->exceptionType= exceptionType;
        this->msg= formattedMsg.str();
        this->status= status;
    }
private:
    string exceptionType;   ///< Type of exception being thrown (i.e. Socket? UnknownHost?)
    string msg;             ///< Error message for the exception
    int status;             ///< Status code for the exception
};

}   //namespace cpputilities
}   //namespace etsai

#endif


