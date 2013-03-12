#include "CppUtilities/Network/Socket.h"
#include "CppUtilities/Network/InetAddress.h"
#include "CppUtilities/Core/StatusCodes.h"

#ifdef WIN32
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif
#include <sstream>
#include <vector>

namespace etsai {
namespace cpputilities {

using std::string;
using std::stringstream;
using std::vector;

Socket::Socket() throw(SocketException) {
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw exception(SocketException, "Error initializing Winsock", ERROR_INTERNAL);
    }
    winsockCleanup= true;
#endif

    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw exception(SocketException, "Cannot create TCP socket", ERROR_INTERNAL);
    }

    connected= false;
    closed= false;
}

Socket::Socket(const std::string& hostname, int port) throw(SocketException) : Socket() {
    connect(hostname, port);
}

Socket::Socket(int tcpSocket, sockaddr_in *addr) {
    this->tcpSocket= tcpSocket;
    connectionInfo.sin_family= addr->sin_family;
    connectionInfo.sin_port= addr->sin_port;
    connectionInfo.sin_addr= addr->sin_addr;
    
    connected= true;
    closed= false;
#ifdef WIN32
    winsockCleanup= false;
#endif
}

Socket::~Socket() {
    close();
}

void Socket::close() {
    if (!closed) {
#ifdef WIN32
        closesocket(tcpSocket);
        if (winsockCleanup) {
            WSACleanup();
        }
#else
        ::close(tcpSocket);
#endif
        closed= true;
        connected= false;
    }
}

void Socket::connect(const std::string& hostname, int port) throw(SocketException) {
    if (closed) {
        throw exception(SocketException, "Socket is closed", ERROR_USAGE);
    }
    if (connected) {
        throw exception(SocketException, "Already connected to a remote machine", ERROR_USAGE);
    }

    bool success= false;
    vector<InetAddress> results= InetAddress::getByName(hostname);
    connectionInfo.sin_family= AF_INET;
    connectionInfo.sin_port= htons(port);

    for(auto it= results.begin(); !success && it != results.end(); it++) {
        int result;

        connectionInfo.sin_addr= it->getAddress();
        result= ::connect(tcpSocket,(sockaddr *) &connectionInfo, sizeof(connectionInfo));
        success= success || result >= 0;
    }
    if (!success) {
        throw exception(SocketException, "Cannot connect to " + getAddressPort(), ERROR_INTERNAL);
    }

    connected= true;
}

void Socket::write(const std::string& msg) throw(SocketException) {
    if (closed) {
        throw exception(SocketException, "Socket closed, cannot write", ERROR_USAGE);
    }
    if (!connected) {
        throw exception(SocketException, "Socket not connected, cannot write", ERROR_USAGE);
    }

    int nBytes;

#ifndef WIN32
    nBytes= ::write(tcpSocket, msg.c_str(), msg.length());
#else
    nBytes= send(tcpSocket, msg.c_str(), msg.length(), 0);
#endif
    if (nBytes < 0) {
        throw exception(SocketException, "Cannot write to " + getAddressPort(), ERROR_INTERNAL);
    }
}

std::string Socket::read(unsigned int nBytes) throw(SocketException) {
    if (closed) {
        throw exception(SocketException, "Socket closed, cannot read", ERROR_USAGE);
    }
    if (!connected) {
        throw exception(SocketException, "Socket not connected, cannot read", ERROR_USAGE);
    }

    string msg;
    char buffer[2]= {'\0', '\0'};
    int readBytes;

    do {
#ifndef WIN32
        readBytes= ::read(tcpSocket, buffer, sizeof(buffer) - 1);
#else
        readBytes= recv(tcpSocket, buffer, sizeof(buffer) - 1, 0);
#endif

        if (readBytes < 0) {
            throw exception(SocketException, "Cannot read from " + getAddressPort(), ERROR_INTERNAL);
        } else {
            /**
             * Throw out \\n in a \\r\\n sequence. The readLine function sets
             * readCarriage to true if \\r is read, then terminates. This only
             * applies to readLine. A normal read will consume everything
*/
            if (!readCarriage || buffer[0] != '\n') {
                msg+= buffer;
            }
            readCarriage= false;
        }
    } while(msg.length() < nBytes && readBytes == sizeof(buffer)-1);

    return msg;
}

std::string Socket::readLine() throw(SocketException) {
    string msg, ch;
    auto terminate= [this](string ch) -> bool {
        readCarriage= ch == "\r";
        return readCarriage || ch == "\n";
    };

    while(!terminate((ch= read(1)))) {
        msg+= ch;
    }
    return msg;
}

bool Socket::isConnected() const {
    return connected;
}

bool Socket::isClosed() const {
    return closed;
}

int Socket::getPort() const {
    return ntohs(connectionInfo.sin_port);
}

std::string Socket::getAddress() const {
    return inet_ntoa(connectionInfo.sin_addr);
}

std::string Socket::getAddressPort() const {
    stringstream msg;

    msg << getAddress() << ":" << getPort();
    return msg.str();
}

}   //namespace cpputilities
}   //namespace etsai
