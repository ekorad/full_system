#include "BasicServer.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <system_error>
#include <cerrno>

using std::system_error;
using std::system_category;
using std::runtime_error;
using std::to_string;

BasicServer::BasicServer(const int port)
{
    _fdServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (_fdServerSock == -1)
    {
        const auto error = system_error(errno, system_category(), "Could not create server socket");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        logger().log("Initialized server socket with descriptor: " + to_string(_fdServerSock),
            GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    constexpr int level = SOL_SOCKET;
    constexpr int optsName = SO_REUSEADDR | SO_REUSEPORT;
    constexpr int optsVal = 1;

    if (setsockopt(_fdServerSock, level, optsName, &optsVal, sizeof(optsVal)) == -1)
    {
        const auto error = system_error(errno, system_category(), "Could not set socket options");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        closeServerSocket();
        throw error;
    }
    else
    {
        logger().log("Successfully set socket options", GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    _addrServer.sin_family = AF_INET;
    _addrServer.sin_addr.s_addr = INADDR_ANY;
    _addrServer.sin_port = htons(port);

    if (bind(_fdServerSock, (struct sockaddr *)&_addrServer, sizeof(_addrServer)) == -1)
    {
        const auto error = system_error(errno, system_category(), "Could not bind address to socket");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        closeServerSocket();
        throw error;
    }
    else
    {
        logger().log("Bound address to socket (port: " + to_string(port) + ")",
            GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    constexpr int maxNumClients = 1;
    if (listen(_fdServerSock, maxNumClients) == -1)
    {
        const auto error = system_error(errno, system_category(), "Could not mark socket for listen");
        logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        closeServerSocket();
        throw error;
    }
    else
    {
        logger().log("Marked server socket for listen", GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    logger().log("Server initialization successful", GENERATE_CONTEXT());
}

BasicServer::~BasicServer()
{
    disconnect();
    closeServerSocket();
}

void BasicServer::awaitConnection()
{
    socklen_t clientAddrLen = sizeof(sockaddr_in);

    logger().log("Awaiting connection from client...", GENERATE_CONTEXT());
    _fdClientSock = accept(_fdServerSock, reinterpret_cast<sockaddr*>(&_addrClient), &clientAddrLen);
    if (_fdClientSock == -1)
    {
        const auto error = system_error(errno, system_category(), "Connection failed");
    }

    optional<string> ipAddrStrOpt = Utils::convertIPAddressToString(_addrClient.sin_addr);
    string ipAddrStr;

    if (!ipAddrStrOpt.has_value())
    {
        logger().log("Could not convert client IP address "
            + to_string(_addrClient.sin_addr.s_addr) + " to string",
            GENERATE_CONTEXT(), LogLevel::WARNING);
    }
    else
    {
        ipAddrStr = ipAddrStrOpt.value();
    }

    logger().log("Client with IP address " + ipAddrStr + " connected successfully",
        GENERATE_CONTEXT());
}

void BasicServer::close()
{
    disconnect();

    if (closeServerSocket() == false)
    {
        logger().log("Server already closed", GENERATE_CONTEXT());
    }
}

void BasicServer::disconnectClient()
{
    if (disconnect() == false)
    {
        logger().log("No client connected", GENERATE_CONTEXT());
    }
}

bool BasicServer::closeServerSocket()
{
    if (_fdServerSock != -1)
    {
        int fd = _fdServerSock;
        ::close(_fdServerSock);
        _fdServerSock = -1;

        logger().log("Closed server socket (descriptor = " + to_string(fd) + ")",
            GENERATE_CONTEXT());

        return true;
    }

    return false;
}

bool BasicServer::disconnect()
{
    if (_fdClientSock != -1)
    {
        optional<string> ipAddrStrOpt = Utils::convertIPAddressToString(_addrClient.sin_addr);
        string ipAddrStr;

        if (!ipAddrStrOpt.has_value())
        {
            logger().log("Could not convert client IP address "
                + to_string(_addrClient.sin_addr.s_addr) + " to string",
                GENERATE_CONTEXT(), LogLevel::WARNING);
        }
        else
        {
            ipAddrStr = ipAddrStrOpt.value();
        }

        ::close(_fdClientSock);
        _fdClientSock = -1;
        _addrClient = {};

        logger().log("Disconnected client with IP address " + ipAddrStr,
            GENERATE_CONTEXT());

        return true;
    }

    return false;
}