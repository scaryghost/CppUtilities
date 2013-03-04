#ifndef ETSAI_CPPUTILITIES_CONSOLEHANDLER
#define ETSAI_CPPUTILITIES_CONSOLEHANDLER

#include "CppUtilities/Logging/Handler.h"

#include <iostream>

namespace etsai {
namespace cpputilities {

/**
 * Sends messages to the console
 * @author etsai
 */
class ConsoleHandler : public Handler {
public:
    ConsoleHandler() : Handler(Level::INFO) {}

    virtual bool publish(const string &msg) { cout << msg << endl; return true; }
    virtual void close() { return; }
};

}   //namespace cpputilities
}   //namespace etsai

#endif
