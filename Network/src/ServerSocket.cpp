#include "CppUtilities/Network/ServerSocket.h"
#include "CppUtilities/Core/StatusCodes.h"

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
using std::shared_ptr;

ServerSocket::ServerSocket() throw(SocketException) {
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        throw exception(SocketException, "Error initializing Winsock", ERROR_INTERNAL);
    }
#endif

    tcpSocket= socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0) {
        throw exception(SocketException, "Cannot create TCP Socket", ERROR_INTERNAL);
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
        throw exception(SocketException, "Cannot bind to port: server socket is closed", ERROR_USAGE);
    }
    if (bound) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Socket already bound to port " << ntohs(serverInfo.sin_port);
        throw exception(SocketException, errorMsg.str(), ERROR_USAGE);
    }

    serverInfo.sin_family= AF_INET;
    serverInfo.sin_addr.s_addr= INADDR_ANY;
    serverInfo.sin_port= htons(port);

    if (::bind(tcpSocket, (sockaddr *) &serverInfo, sizeof(serverInfo)) < 0) {
        stringstream errorMsg(stringstream::out);

        errorMsg << "Cannot bind to port " << port;
        throw exception(SocketException, errorMsg.str(), ERROR_CONFIG);
    }
    listen(tcpSocket, 5);
    bound= true;
}

shared_ptr<Socket> ServerSocket::accept() throw(SocketException) {
    if (!bound) {
        throw exception(SocketException, "Server socket not bound to a port", ERROR_USAGE);
    }
    if (closed) {
        throw exception(SocketException, "Cannot accept connections: server socket is closed", ERROR_USAGE);
    }

    int clientfd;
    sockaddr_in clientAddr;
    socklen_t structSize= sizeof(clientAddr);


    clientfd= ::accept(tcpSocket, (sockaddr *) &clientAddr, &structSize);
    if (clientfd < 0) {
        throw exception(SocketException, "Cannot accept connection", ERROR_INTERNAL);
    }
    return shared_ptr<Socket>(new Socket(clientfd, &clientAddr));
}

void ServerSocket::close() {
    if (!closed) {
#ifdef WIN32
        ::shutdown(tcpSocket, SD_BOTH);
        closesocket(tcpSocket);
        WSACleanup();
#else
        ::shutdown(tcpSocket, SHUT_RDWR);
        ::close(tcpSocket);
#endif
        closed= true;
    }
}

bool ServerSocket::isBound() const {
    return bound;
}

bool ServerSocket::isClosed() const {
    return closed;
}

}   //namespace cpputilities
}   //namespace etsai
