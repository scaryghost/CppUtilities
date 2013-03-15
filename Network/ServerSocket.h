#ifndef STOUGHTON1004LIB_SERVERSOCKET_H
#define STOUGHTON1004LIB_SERVERSOCKET_H

#include "CppUtilities/Network/SocketException.h"
#include "CppUtilities/Network/Socket.h"

#include <memory>

#ifdef WIN32
#include <WinSock2.h>

#pragma warning( disable : 4290 )
#else
#include <netinet/in.h>
#include <sys/socket.h>
#endif

namespace etsai {
namespace cpputilities {

using std::shared_ptr;

/**
 * Implements a server socket, waiting for TCP connections.  This class 
 * will manage the differences between WinSock and Linux socket types
 * @author etsai
 */
class ServerSocket {
public:
    /**
     * Creates an unbounded server socket
     * @throws SocketException If TCP socket cannot be created
     */
    ServerSocket() throw(SocketException);
    /**
     * Creates a server socket bound to the specified port
     * @param   port    Port number to bind the server socket to
     * @param   SocketException If ServerSocket is already bound to another port 
     *                          or if desired port is already taken
     */
    ServerSocket(int port) throw(SocketException);
    /**
     * Closes and shuts down the socket
     */
    ~ServerSocket();

    /**
     * Binds the server socket to the specified port
     * @param   port    Port number to bind the server socket to
     * @throws  SocketException If ServerSocket is already bound to another port 
     *                          or if desired port is already taken
     */
    void bind(int port) throw(SocketException);
    /**
     * Accepts an incoming connection to the server socket.  The function 
     * will block until a connection is available
     * @return  Socket connecting to the client wrapped in a shared_ptr
     * @throws  SocketException If the socket is closed, not bound to a port, or cannot 
     *                          accept the incoming connection
     */
    shared_ptr<Socket> accept() throw(SocketException);
    /**
     * Closes and shuts down the server socket
     */
    void close();

    /**
     * Returns binding state
     * @return  True if the server socket is already bound
     */
    bool isBound() const;
    /**
     * Returns closed state
     * @return  True if the server socket is closed
     */
    bool isClosed() const;

private:
    int tcpSocket;              ///< File descriptor for the socket
    bool bound;                 ///< Stores the bound state
    bool closed;                ///< Stores the closed state
    sockaddr_in serverInfo;     ///< Information about the server socket;
};  //class ServerSocket

}   //namespace cpputilities
}   //namespace etsai

#endif  //STOUGHTON1004LIB_SERVERSOCKET_H
