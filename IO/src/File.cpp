#include "CppUtilities/IO/File.h"

#ifdef WIN32
#include <Windows.h>
#endif

namespace etsai {
namespace cpputilities {

#ifdef WIN32
using std::wstring;
#endif

File::File() : File(".") {
}

File::File(const string& path) :
    path(path) {
    lastStatus= stat(path.c_str(), &fileStat);
}

bool File::mkdir() {
#ifndef WIN32
    bool valid(true);

    if (lastStatus) {
        if (::mkdir(path.c_str(), 0777)) {
            valid= false;
        }
    } else {
        valid= false;
    }
    lastStatus= stat(path.c_str(), &fileStat);
    return valid;
#else
    LPCWSTR pathWStr= wstring(path.begin(), path.end()).c_str();
    return CreateDirectory(pathWStr, NULL) != FALSE;
#endif
}

bool File::mkdirs() {
#ifndef WIN32
    bool valid(true);
    size_t found= path.find_first_of("/");

    while (valid && found != string::npos) {
        if (lastStatus) {
            if (::mkdir(path.substr(0, found).c_str(), 0777)) {
                valid= false;
            }
        }
        found= path.find_first_of("/", found + 1);
    }
    if (valid && path.back() != '/') {
        if (::mkdir(path.c_str(), 0777)) {
            valid= false;
        }
    }
    lastStatus= stat(path.c_str(), &fileStat);
    return valid;
#else
    LPCWSTR pathWStr= wstring(path.begin(), path.end()).c_str();
    return CreateDirectory(pathWStr, NULL) != FALSE;
#endif
}

bool File::isDirectory() const {
    return !lastStatus && (fileStat.st_mode & S_IFDIR) == S_IFDIR;
}

bool File::isFile() const {
    return !lastStatus && (fileStat.st_mode & S_IFREG) == S_IFREG;
}

bool File::exists() const {
    return !lastStatus;
}

const string& File::getPath() const {
    return path;
}

}
}
