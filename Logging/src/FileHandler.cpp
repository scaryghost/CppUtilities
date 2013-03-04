#include "CppUtilities/Logging/FileHandler.h"

#include "CppUtilities/Network/InetAddress.h"
#include "CppUtilities/Core/StatusCodes.h"

#include <ctime>

namespace etsai {
namespace cpputilities {

using std::time_t;
using std::tm;

FileHandler::FileHandler() throw(FileException) : Handler(Level::INFO) {
    time_t curr;
    const char* format= "_%Y-%m-%d_%H-%M-%S";
    char timeStamp[80];

    time(&curr);
#ifdef WIN32
    tm timeInfo;
    localtime_s(&timeInfo, &curr);
    strftime(timeStamp, sizeof(timeStamp), format, &timeInfo);
#else
    tm* timeInfo;
    timeInfo= localtime(&curr);
    strftime(timeStamp, sizeof(timeStamp), format, timeInfo);
#endif
    filename= InetAddress::getLocalHostName() + timeStamp + ".log";

    open();
}

FileHandler::FileHandler(const std::string filename) throw(FileException) : Handler(Level::INFO) {
    this->filename= filename;
    open();
}

FileHandler::~FileHandler() {
    close();
}

void FileHandler::open() throw(FileException) {
    fd.open(filename.c_str());
    if (!fd) {
        throw exception(FileException, "Error opening file: " + filename + " for logging", ERROR_CONFIG);
    }
}

bool FileHandler::publish(const std::string &msg) {
    fd << msg << "\n";
    fd.flush();
    return true;
}

void FileHandler::close() {
    fd.close();
}

}
}
