#include "CppUtilities/Cli/CliBuilder.h"
#include "CppUtilities/Core/StatusCodes.h"

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>

namespace etsai {
namespace cpputilities {

using std::cout;
using std::endl;
using std::exit;
using std::map;
using std::string;
using std::stringstream;

CliBuilder CliBuilder::instance;

CliBuilder* CliBuilder::getBuilder() {
    return &instance;
}

CliBuilder& CliBuilder::addOption(const Option& opt) throw(CliOptionException) {
    stringstream excep(stringstream::out);

    if (options.count(opt.optName) != 0) {
        excep << "Option " << opt.optName << " already registered";
        throw exception(CliOptionException, excep.str(), ERROR_CONFIG);
    }
    options[opt.optName]= opt;
    if (!opt.longOpt.empty()) {
        if (options.count(opt.longOpt) != 0) {
            excep << "Option " << opt.optName << "(" << opt.longOpt << ") already registered";
            throw exception(CliOptionException, excep.str(), ERROR_CONFIG);
        }
        options[opt.longOpt]= opt;
    }
    uniqueOpts.insert(&options[opt.optName]);
    return *this;
}

CliBuilder& CliBuilder::setUsage(const string& usage) {
    this->usage= usage;
    return *this;
}

void CliBuilder::parse(int argc, char **argv) throw(CliOptionException) {
    int i= 0;
    stringstream excep(stringstream::out);

    while(i < argc) {
        if (argv[i][0] == '-') {
            if (options.count(argv[i]) == 0) {
                excep << "Invalid option read (" << argv[i] << ")";
                throw exception(CliOptionException, excep.str(), ERROR_CONFIG);
            }

            Option opt= options[argv[i]];
            Arguments args;

            options.erase(argv[i]);
            if (opt.args > 0) {
                if (i + 1 < argc) {
                    args.addArgs(argv[i+1], opt.separator);
                }
                if (args.size() != opt.args) {
                    excep << "Option (" << opt.optName << ") requires " << opt.args << " arguments, was given " << args.size();
                    throw exception(CliOptionException, excep.str(), ERROR_CONFIG);
                }
                i+= 2;
            } else {
                i++;
            }
            opt.callback(args);
        } else {
            i++;
        }
    }

    for(auto it= options.begin(); it != options.end(); it++) {
        if ((it->second).required) {
            throw exception(CliOptionException, "Required option was not used (" + it->second.optName + ")", ERROR_CONFIG);
        }
    }
}

void CliBuilder::displayUsage() {
    unsigned int maxOptionLength= 0;
    map<string,Option*> displayNames;
    auto displayOption= [](const Option& opt) -> string {
        string display= " ";
    
        display+= opt.optName;
        if (!opt.longOpt.empty()) {
            display+= ", " + opt.longOpt;
        }
        if (!opt.argName.empty()) {
            display+= " <" + opt.argName + ">";
        }
        return display;
    };

    for(auto opt: uniqueOpts) {
        string display(displayOption(*opt));
        displayNames[display]= opt;
        auto displayLength= display.size();
        maxOptionLength= maxOptionLength > displayLength ? maxOptionLength : displayLength;
    }
    cout << "usage: " << usage << endl;
    for(auto &names: displayNames) {
        string filler(maxOptionLength - names.first.length(), ' ');

        cout << names.first << filler << "\t" << names.second->description << endl;
    }
    exit(0);
}

CliBuilder::CliBuilder() {
}

}
}
