#include "CppUtilities/IO/File.h"

namespace etsai {
namespace cpputilities {

File::File() : File(".") {
}

File::File(const string& path) :
    path(path) {
    lastStatus= stat(path.c_str(), &fileStat);
}

bool File::mkdir() {
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
}

bool File::mkdirs() {
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
}

bool File::isDirectory() const {
    return !lastStatus && S_ISDIR(fileStat.st_mode);
}

bool File::isFile() const {
    return !lastStatus && S_ISREG(fileStat.st_mode);
}

bool File::exists() const {
    return !lastStatus;
}

const string& File::getPath() const {
    return path;
}

}
}
