#ifndef ETSAI_CPPUTILITIES_INETADDRESS
#define ETSAI_CPPUTILITIES_INETADDRESS

#include "CppUtilities/Network/UnknownHostException.h"
#include "CppUtilities/Network/SocketException.h"

#include <string>
#include <unordered_map>
#include <vector>

#ifndef WIN32
#include <netinet/in.h>
#else
#include <WinSock2.h>
#pragma warning( disable : 4290 )
#endif

namespace etsai {
namespace cpputilities {

using std::string;
using std::unordered_map;
using std::vector;

/**
* Manages host name lookups, mapping host names to ip addresses.
* The functionality is based off the Java class of the same name.
* @author etsai
*/
class InetAddress {
public:
    /**
     * Get a list of all IP addresses of the given host name
     * @param hostName Host name to lookup
     * @return All IP addresses of the host name
     * @throw UnknownHostException If host name cannot be resolved
     * @throw SocketException If WinSock failed to initialize (windows only)
     */
    static const vector<InetAddress>& getByName(const string &hostName) throw(UnknownHostException,SocketException);

    /**
     * Get the host name of the local machine
     * @return Host name of the local machine
     */
    static std::string getLocalHostName() throw (SocketException);

    /**
     * Get the raw IP address of the object
     * @return raw IP address
     */
    in_addr getAddress() const;
    /**
     * Get the IP address as text
     * @return textual IP address
     */
    string getHostAddress() const;
    /**
     * Get the host name of the IP address
     * @return host name
     */
    string getHostName() const;

private:
    /** Cache of successful host name lookups */
    static unordered_map<string, vector<InetAddress> > resultsCache;

    /**
     * Default constructor.
     * Set as private so users cannot create their own InetAddress object outside of using the static function
     */
    InetAddress();

    string hostName;   ///< Host name
    string ipAddr;     ///< Text version of the ip address
    in_addr rawIpAddr;      ///< Raw IP address
};

}   //namespace cpputilities
}   //namespace etsai

#endif
