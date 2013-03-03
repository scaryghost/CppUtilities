#include "CppUtilities/Network/InetAddress.h"
#include "CppUtilities/Core/StatusCodes.h"

#include <mutex>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace etsai {
namespace cpputilities {

using std::lock_guard;
using std::mutex;

unordered_map<string, vector<InetAddress> > InetAddress::resultsCache;
mutex resultsCacheMutex;

const vector<InetAddress>& InetAddress::getByName(const string &hostName) throw(UnknownHostException) {
    {
        lock_guard<mutex> lock(resultsCacheMutex);
        if (resultsCache.count(hostName) != 0) {
            return resultsCache[hostName];
        }
    }

    vector<InetAddress> results;
    addrinfo hints, *res, *next;
    int err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_family= AF_INET;

    if ((err= getaddrinfo(hostName.c_str(), NULL, &hints, &res)) != 0) {
        throw exception(UnknownHostException, "Cannot resolve: " + hostName, ERROR_CONFIG);
    }

    for(next= res; next != NULL; next= next->ai_next) {
        InetAddress addr;
        addr.rawIpAddr.s_addr= ((sockaddr_in *)(next->ai_addr))->sin_addr.s_addr;
        addr.ipAddr= inet_ntoa(addr.rawIpAddr);
        addr.hostName= hostName;
        results.push_back(addr);
    }

    {
        lock_guard<mutex> lock(resultsCacheMutex);
        resultsCache[hostName]= results;

        return resultsCache[hostName];
    }
}

string InetAddress::getLocalHostName() {
    char hostname[128];

    gethostname(hostname, sizeof(hostname));
    return hostname;
}

InetAddress::InetAddress() {
}

in_addr InetAddress::getAddress() const {
    return rawIpAddr;
}

string InetAddress::getHostAddress() const {
    return ipAddr;
}

string InetAddress::getHostName() const {
    return hostName;
}

}   //namespace cpputilities
}   //namespace etsai
