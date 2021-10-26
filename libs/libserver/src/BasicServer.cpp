#include "BasicServer.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <system_error>
#include <cerrno>

using std::system_error;
using std::system_category;
using std::to_string;

BasicServer::BasicServer(const int port)
    : _port{ port }
{
    _fdServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (_fdServerSock == -1)
    {
        auto error = system_error(errno, system_category(), "Could not create socket");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        logger().log("Initialized socket with descriptor: " + to_string(_fdServerSock),
            GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    constexpr int level = SOL_SOCKET;
    constexpr int optsName = SO_REUSEADDR | SO_REUSEPORT;
    constexpr int optsVal = 1;

    if (setsockopt(_fdServerSock, level, optsName, &optsVal, sizeof(optsVal)) == -1)
    {
        auto error = system_error(errno, system_category(), "Could not set socket options");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        logger().log("Successfully set socket options", GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    _addrServer.sin_family = AF_INET;
    _addrServer.sin_addr.s_addr = INADDR_ANY;
    _addrServer.sin_port = htons(_port);

    if (bind(_fdServerSock, (struct sockaddr *)&_addrServer, sizeof(_addrServer)) == -1)
    {
        auto error = system_error(errno, system_category(), "Could not bind address to socket");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        logger().log("Bound address to socket (port: " + to_string(_port) + ")",
            GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    constexpr int numClients = 1;
    if (listen(_fdServerSock, numClients) == -1)
    {
        auto error = system_error(errno, system_category(), "Could not listen on socket with descriptor"
            + to_string(_fdServerSock) + ", closing descriptor");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        close(_fdServerSock);
        throw error;
    }
    else
    {
        logger().log("Marked socket with descriptor " + to_string(_fdServerSock)
            + " for listen", GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    logger().log("Server initialization successful, listening on port "
        + to_string(_port), GENERATE_CONTEXT());
}

BasicServer::~BasicServer()
{
    close(_fdServerSock);
    logger().log("Closed server", GENERATE_CONTEXT());
}

void BasicServer::awaitConnection()
{
    socklen_t clientAddrLen = sizeof(struct sockaddr_in);

    logger().log("Awaiting connection from client...", GENERATE_CONTEXT());
    _fdClientSock = accept(_fdServerSock, reinterpret_cast<sockaddr*>(&_addrClient), &clientAddrLen);
    if (_fdClientSock == -1)
    {
        throw system_error(errno, system_category(), "Connection failed");
    }

    char ipAddr[INET_ADDRSTRLEN];
    string ipAddrStr;
    const char* retVal = inet_ntop(AF_INET, &(_addrClient.sin_addr), ipAddr, INET_ADDRSTRLEN);
    if (retVal == nullptr)
    {
        ipAddrStr = to_string(_addrClient.sin_addr.s_addr);

        logger().log("Could not convert client IP address "
            + ipAddrStr + " to string",
            GENERATE_CONTEXT(), LogLevel::WARNING);
    }

    logger().log("Client with IP address " + ipAddrStr + " connected successfully",
        GENERATE_CONTEXT());
}