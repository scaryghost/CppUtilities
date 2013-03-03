#include "CppUtilities/Network/ServerSocket.h"

#include <sstream>
#ifdef WIN32
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

typedef int socklen_t;
#else
#include <unistd.h>
#endif

namespace etsai {
namespace cpputilities {

using std::stringstream;

ServerSocket::ServerSocket() throw(SocketException) {
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw SocketException("Error initializing Winsock", __FUNCTION__, __LINE__, 1);
    }
#endif

    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw SocketException("Cannot create TCP Socket", __FUNCTION__, __LINE__, 1);
    }
    bound= false;
    closed= false;
}

ServerSocket::ServerSocket(int port) throw(SocketException) : ServerSocket() {
    bind(port);
}

ServerSocket::~ServerSocket() {
    close();
}

void ServerSocket::bind(int port) throw(SocketException) {
    if (closed) {
        throw SocketException("Cannot bind to port: server socket is closed", __FUNCTION__, __LINE__, 1);
    }
    if (bound) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Socket already bound to port " << ntohs(serverInfo.sin_port);
        throw SocketException(errorMsg.str(), __FUNCTION__, __LINE__, 1);
    }

    serverInfo.sin_family= AF_INET;
    serverInfo.sin_addr.s_addr= INADDR_ANY;
    serverInfo.sin_port= htons(port);

    if (::bind(tcpSocket, (sockaddr *) &serverInfo, sizeof(serverInfo)) < 0) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Cannot bind to port " << port;
        throw SocketException(errorMsg.str(), __FUNCTION__, __LINE__, 1);
    }
    listen(tcpSocket, 5);
    bound= true;
}

Socket ServerSocket::accept() throw(SocketException) {
    if (!bound) {
        throw SocketException("Server socket not bound to a port", __FUNCTION__, __LINE__, 1);
    }
    if (closed) {
        throw SocketException("Cannot accept connections: server socket is closed", __FUNCTION__, __LINE__, 1);
    }

    int clientfd;
    sockaddr_in clientAddr;
    socklen_t structSize= sizeof(clientAddr);


    clientfd= ::accept(tcpSocket, (sockaddr *) &clientAddr, &structSize);
    if (clientfd < 0) {
        throw SocketException("Cannot accept connection", __FUNCTION__, __LINE__, 1);
    }
    return Socket(clientfd, &clientAddr);
}

void ServerSocket::close() {
#ifdef WIN32
    closesocket(tcpSocket);
    WSACleanup();
#else
    ::close(tcpSocket);
#endif
    closed= true;
}

bool ServerSocket::isBound() const {
    return bound;
}

bool ServerSocket::isClosed() const {
    return closed;
}

}   //namespace cpputilities
}   //namespace etsai
