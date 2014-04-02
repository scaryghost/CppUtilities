#ifndef ETSAI_CPPUTILITIES_FILEHANDLER
#define ETSAI_CPPUTILITIES_FILEHANDLER

#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

#include "FileException.h"
#include "Handler.h"
#include "CppUtilities/IO/File.h"

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
     * @param   dir             Directory to store the log file in
     * @throws  FileException   If the file failed to open, directory failed to be created, or 
     *                          directory path is not a directory
     */
    FileHandler(const string& dir) throw(FileException);
    /**
     * Create a FileHandler, writing to the given filename.  If the file exists, it will 
     * be overwritten
     * @param   dir             Directory to store the log file in
     * @param   filename        Name of the log file to write to.
     * @throw   FileException   If the file failed to open, directory failed to be created, or 
     *                          directory path is not a directory
     */
    FileHandler(const string& dir, const string filename) throw(FileException);
    /**
     * Close file resources
     */
    ~FileHandler();

    virtual bool publish(const string &msg);
    virtual void close();

private:
    File fileDir;           ///< Directory the log file will reside in
    string filename;        ///< Name of the file to write to
    ofstream fd;            ///< Log's file descriptor

    /**
     * Open the log file for writing.  Need this function since default constructor generates the filename
     * @throw   FileException   If the file failed to open
     */
    void open() throw(FileException);
};  //class FileHandler

}   //namespace cpputilities
}   //namespace etsai

#endif 
