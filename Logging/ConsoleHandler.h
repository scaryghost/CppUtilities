#ifndef ETSAI_CPPUTILITIES_CONSOLEHANDLER
#define ETSAI_CPPUTILITIES_CONSOLEHANDLER

#include "Handler.h"

#include <iostream>

namespace etsai {
namespace cpputilities {

using std::cout;
using std::endl;

/**
 * Sends messages to the console
 * @author etsai
 */
class ConsoleHandler : public Handler {
public:
    ConsoleHandler() : Handler(Level::CONFIG) {}

    virtual bool publish(const string &msg) { cout << msg << endl; return true; }
    virtual void close() { return; }
};

}   //namespace cpputilities
}   //namespace etsai

#endif
