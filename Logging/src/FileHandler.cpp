#include "CppUtilities/Logging/FileHandler.h"

#include "CppUtilities/Network/InetAddress.h"
#include "CppUtilities/Core/StatusCodes.h"

#include <ctime>
#include <iostream>

namespace etsai {
namespace cpputilities {

using std::endl;
using std::time_t;
using std::tm;

FileHandler::FileHandler(const string& dir) throw(FileException) : Handler(Level::INFO), fileDir(dir) {
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

FileHandler::FileHandler(const string& dir, const std::string filename) throw(FileException) : Handler(Level::INFO),
    fileDir(dir), filename(filename) {
    open();
}

FileHandler::~FileHandler() {
    close();
}

void FileHandler::open() throw(FileException) {
    string fullpath(fileDir.getPath() + "/" + filename);
    if (fileDir.exists()) {
        if (!fileDir.isDirectory()) {
            throw exception(FileException, "Given path for logs is not a directory: " + fileDir.getPath(), ERROR_CONFIG);
        }
    } else if (!fileDir.mkdirs()) {
        throw exception(FileException, "Error creating log directory: " + fileDir.getPath(), ERROR_CONFIG);
    }

    fd.open(fullpath.c_str());
    if (!fd) {
        throw exception(FileException, "Error opening file: " + fullpath + " for logging", ERROR_CONFIG);
    }
}

bool FileHandler::publish(const std::string &msg) {
    fd << msg << endl;
    return true;
}

void FileHandler::close() {
    fd.close();
}

}
}
