#ifndef ETSAI_CPPUTILITIES_CLIBUILDER
#define ETSAI_CPPUTILITIES_CLIBUILDER

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include "CppUtilities/Cli/CliOptionException.h"
#include "CppUtilities/Cli/Option.h"

#include <map>
#include <string>

namespace etsai {
namespace cpputilities {

using std::map;
using std::string;

/**
 * Builder for processing command line arguments
 * @author etsai
 */
class CliBuilder {
public:
    /**
     * Get the builder object
     * @return  CliBuilder instance
     */
    static CliBuilder* getBuilder();

    /**
     * Add an option to the collection
     * @param   opt     Option to add
     * @return  Reference to the calling object
     * @throw   CliOptionException   If a duplicate option has already been acted
     */
    CliBuilder& addOption(const Option& opt) throw(CliOptionException);
    /**
     * Set the usage message
     * @param   usage   Usage description
     * @return  Reference to the calling object
     */
    CliBuilder& setUsage(const string& usage);

    /**
     * Parse the command line arguments and execute the callback functions
     * @param   argc    Number of arguments
     * @param   argv    Array of arguments passed in
     * @throw   CliOptionException   If invalid option was passed in or not enough 
     * arguments were given for an option
     */
    void parse(int argc, char **argv) throw(CliOptionException);
    /**
     * Print the usage message, and then terminate
     */
    void displayUsage();

private:
    CliBuilder();                       ///< Default constructor.  Hidden to make singleton

    static CliBuilder instance;         ///< Single instance of the class
    map<string, Option> options;        ///< Map of added options
    string usage;                       ///< Usage message for the program
};  //class CliBuilder

}   //namesapce cpputilities
}   //namespace etsai

#endif
