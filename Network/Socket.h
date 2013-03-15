#ifndef STOUGHTON1004LIB_SOCKET_H
#define STOUGHTON1004LIB_SOCKET_H

#include "CppUtilities/Network/SocketException.h"

#include <string>
#ifdef WIN32
#include <WinSock2.h>

#pragma warning( disable : 4290 )
#else
#include <netinet/in.h>
#include <sys/socket.h>
#endif

namespace etsai {
namespace cpputilities {

class ServerSocket;

/**
* Implements a TCP socket, able to connect to a remote host and exchange information
* with the host. This class will manage the differences between Linux and WinSock
* @author etsai
*/
class Socket {
public:
    /**
     * Create an unconnected socket
     * @throws  SocketException If TCP socket cannot be created
     */
    Socket() throw(SocketException);
    /**
     * Create a TCP socket, connected to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     * @throws  SocketException If a connection cannot be made to hostname:port
     */
    Socket(const std::string& hostname, int port) throw(SocketException);
    /**
     * Closes and shuts down the socket
     */
    ~Socket();

    /**
     * Close and shuts down the connection
     */
    void close();
    /**
     * Connect to the given hostname and port
     * @param   hostname    Host to connect to
     * @param   port        Port number to connect to
     * @param   SocketException If the socket is closed, already connected to another remote machine, or 
     *                          cannot connect to hostname:port
     */
    void connect(const std::string& hostname, int port) throw(SocketException);
    /**
     * Write the message to the connection
     * @param   msg     Message to be written
     * @throws  SocketException If the socket is closed, not connected, or cannot write to the remote machine 
     */
    void write(const std::string& msg) throw(SocketException);
    /**
     * Reads messages from the connection. Reading stops when either there is nothing left or the number 
     * of bytes given has been read. If there is nothing to read when the function is called, it will
     * block until something is available to be read 
     * @param   nByte   sNumber of bytes to read
     * @return  Message of at most nBytes length
     * @throws  SocketException If the socket is closed, not connected, or cannot read from the remote machine
     */
    std::string read(unsigned int nBytes) throw(SocketException);
    /**
     * Read characters from the connection until one of \\n, \\r, or \\r\\n is read. The message will not contain 
     * the end of line characters. If a newline or return carriage is not in the message, the function will
     * block until one is read. 
     * @return A line of characters from the connection
     * @throws  SocketException If the socket is closed, not connected, or cannot read from the remote machine
     */
    std::string readLine() throw(SocketException);

    /**
     * Returns the connected state of the socket
     * @return True if the socket is connected
     */
    bool isConnected() const;
    /**
     * Returns the close state.  If the socket is closed, it cannot be used
     * @return True if the socket is closed
     */
    bool isClosed() const;
    /**
     * Returns the remote port number the socket is connected to
     * @return Port number connected to
     */
    int getPort() const;
    /**
     * Returns the remote IP address the socket is connected to as text
     * @return IP address connected to
     */
    std::string getAddress() const;
    /**
     * Returns the address and port of the remote connection in address:port form
     * @return Address and port in address:port form
     */
    std::string getAddressPort() const;

private:
    /**
     * Private constructor for building a Socket object when the
     * file descriptor and address information are already known
     * @param   tcpSocket   File descriptor of the TCP socket
     * @para    maddr       Address information about the connection
     */
    Socket(int tcpSocket, sockaddr_in *addr);

    bool readCarriage;              ///< True if a return carriage was read by readLine
    bool closed;                    ///< Stores the closed state
    bool connected;                 ///< Store the connected state
    int tcpSocket;                  ///< Socket file descriptor
    sockaddr_in connectionInfo;     ///< Information about the connection
#ifdef WIN32
    bool winsockCleanup;            ///< True if WSACleanup needs to be called
#endif

    friend class ServerSocket;      ///< Allow ServerSocket access to private variables/functions
}; //class Socket

}   //namespace cpputilities
}   //namespace etsai

#endif
