#ifndef ETSAI_CPPUTILITIES_FILEHANDLER
#define ETSAI_CPPUTILITIES_FILEHANDLER

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include "CppUtilities/Logging/FileException.h"
#include "CppUtilities/Logging/Handler.h"

#include <fstream>
#include <string>

namespace etsai {
namespace cpputilities {

using std::ofstream;
using std::string;

/**
 * Sends messages to a file
 * @author etsai
 */
class FileHandler : public Handler {
public:
    /**
     * Create a FileHandler with a generated log name based on the current date and time
     * @throws  FileException   If the file failed to open
     */
    FileHandler() throw(FileException);
    /**
     * Create a FileHandler, writing to the given filename.  If the file exists, it will 
     * be overwritten
     * @param   filename    Name of the log file to write to.
     * @throw   FileException   If the file failed to open
     */
    FileHandler(const string filename) throw(FileException);
    /**
     * Close file resources
     */
    ~FileHandler();

    virtual bool publish(const string &msg);
    virtual void close();

private:
    /**
     * Open the log file for writing.  Need this function since default constructor generates the filename
     * @throw   FileException   If the file failed to open
     */
    void open() throw(FileException);

    string filename;       ///< Name of the file to write to
    ofstream fd;           ///< Log's file descriptor
};  //class FileHandler

}   //namespace cpputilities
}   //namespace etsai

#endif 
