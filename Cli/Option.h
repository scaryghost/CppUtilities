#ifndef ETSAI_CPPUTILITIES_OPTION
#define ETSAI_CPPUTILITIES_OPTION

#include "CppUtilities/Cli/Arguments.h"

#include <functional>
#include <string>

namespace etsai {
namespace cpputilities {

class CliBuilder;

using std::string;
using std::function;

/**
 * Container for a command line option and its attributes
 * @author etsai
 */
class Option {
public:
    /** Create a type name for the Option's callback action */
    typedef function<void (Arguments)> OptCallback;

    /**
     * Create a blank option.  This is typically only used by classes that need a 
     * default constructor i.e. map or vector
     */
    Option();

    /**
     * Create an option that takes no arguments
     * @param   optName     Name of the argument
     * @param   callback    Callback action to be execute if the option is passed in
     */
    Option(const string& optName, const OptCallback& callback);
    /**
     * Create an option that takes additional arguments
     * @param   optName     Name of the argument
     * @param   separator   Character to separate the arguments
     * @param   args        Number of arguments
     * @param   callback    Callback action to be execute if the option is passed in
     */
    Option(const string& optName, char separator, unsigned int args, const OptCallback& callback);
    
    /**
     * Overloaded assignment operator
     * @param   rhs     Object to copy from
     * @return  Reference to calling object
     */
    Option& operator=(const Option &rhs);
    /**
     * Sets the description
     * @param   description     Description of the option
     * @return  Reference to the calling object
     */
    Option& withDescription(const string& description);
    /**
     * Sets the argument name
     * @param   argName     Name of the argument
     * @return  Reference to the calling object
     */
    Option& withArgName(const string& argName);
    /**
     * Sets the long option name
     * @param   longOpt     Long name of the option
     * @return  Reference to the calling object
     */
    Option& withLongOpt(const string& longOpt);
    /**
     * Sets the required attribute
     * @param   required    True if the option is required
     * @return  Reference to the calling object
     */
    Option& withRequired(bool required);

private:
    string optName;             ///< Short name of the option
    char separator;             ///< Character separator for arguments
    unsigned int args;          ///< Max number of arguments to pass
    OptCallback callback;       ///< Callback action to be run if the option is matched

    bool required;              ///< True if option is required
    string description;         ///< Description of the option
    string argName;             ///< Argument name
    string longOpt;             ///< Long name of the option

    friend class CliBuilder;    ///< Allow CliBuilder to access private member variables
};  //class Option

}   //namespace cpputilities
}   //namespace etsai

#endif
