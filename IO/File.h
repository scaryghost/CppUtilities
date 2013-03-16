#ifndef ETSAI_CPPUTILITIES_FILE
#define ETSAI_CPPUTILITIES_FILE

#include <string>
#include <sys/stat.h>

namespace etsai {
namespace cpputilities {

using std::string;

/**
 * Provides a representation for file and directory path names.  It handles the 
 * coding differences between Windows and Linux.
 * @author etsai
 */
class File {
public:
    /**
     * Constructs object using the currect working directory as the path
     */
    File();
    /**
     * Constructs object using the given path
     * @param   path    Path to work on
     */
    File(const string& path);

    /**
     * Creates the directory pointed to by the object
     * @return  True if succeeded, false otherwise
     */
    bool mkdir();
    /**
     * Creates the directory pointed to by the object and all subdirectories in the path.  
     * Even if the function returns false, some of the subdirectories may have been created.  If 
     * a subdirectory already exists, it will skip it and continue to the next level.
     * @return  True if all directories were created, false otherwise
     */
    bool mkdirs();

    /**
     * Returns true if the path is a directory
     * @return  True if directory
     */
    bool isDirectory() const;
    /**
     * Returns true if the path is a file
     * @return  True if file
     */
    bool isFile() const;
    /**
     * Returns true if path exists
     * @return  True if exists
     */
    bool exists() const;
    /**
     * Gets the path the object is pointing to
     * @Return  Path of the object
     */
    const string& getPath() const;
private:
    string path;                ///< Path the object is pointing to
    int lastStatus;             ///< Status of the last call to stat (Linux only)
    struct stat fileStat;       ///< Current status of the path as filled in by stat (Linux only)
};

}   //namespace cpputilities
}   //namespace etsai

#endif
