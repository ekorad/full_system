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
using std::thread;
using std::unique_lock;
using std::defer_lock;
using std::mutex;
using std::queue;
using std::swap;

BasicServer::BasicServer()
    : DefaultLoggable(defaultLogFileName)
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

    logger().log("Server initialization successful", GENERATE_CONTEXT());
}

BasicServer::~BasicServer()
{
    disconnect();
    closeServerSocket();

    logger().log("Server terminated", GENERATE_CONTEXT());
}

void BasicServer::host(const unsigned port)
{
    sockaddr_in addrServer;

    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = INADDR_ANY;
    addrServer.sin_port = htons(port);

    if (bind(_fdServerSock, (struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
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

    logger().log("Client with IP address " + ipAddrStr + " connected successfully "
        "(descriptor = " + to_string(_fdClientSock) + ")",
        GENERATE_CONTEXT());

    try
    {
        _senderThread = thread{ &BasicServer::senderThreadFunc, this };
    }
    catch(const system_error& error)
    {
        const string& errMsg = "Could not start sender thread";
        const auto thrownError = system_error(error.code().value(), system_category(), errMsg);
        logger().log(errMsg, GENERATE_CONTEXT(), LogLevel::ERROR);
        disconnectClient();
        throw thrownError;
    }

    constexpr int threadStartMillisTmo = 500;
    constexpr int threadStartWaitMillis = 100;
    int threadStartElapsedMilis = 0;
    unique_lock<mutex> lock{ _mutex };

    logger().log("Waiting for sender thread to confirm status...",
        GENERATE_CONTEXT(), LogLevel::DEBUG);
    while (_condVar.wait_for(lock, std::chrono::milliseconds(threadStartElapsedMilis),
        [&]
        {
            return static_cast<bool>(_threadStarted);
        }) == false)
    {
        threadStartElapsedMilis += threadStartWaitMillis;
        if (threadStartElapsedMilis == threadStartMillisTmo)
        {
            const auto error = runtime_error("Could not start sender thread in time");
            logger().log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
            disconnectClient();
            throw error;
        }
    }

    logger().log("Sender thread confirmed status", GENERATE_CONTEXT(), LogLevel::DEBUG);
}

void BasicServer::close()
{
    disconnect();

    if (closeServerSocket() == false)
    {
        logger().log("Server already clossed", GENERATE_CONTEXT());
    }
}

void BasicServer::disconnectClient()
{
    if (disconnect() == false)
    {
        logger().log("No client connected", GENERATE_CONTEXT());
    }
}

void BasicServer::send(const string& message)
{
    unique_lock<mutex> lock{ _mutex };

    _msgQueue.push(message);

    if (!_notified)
    {
        _notified = true;
        logger().log("Notifying sender thread, current message batch size is: "
            + to_string(_msgQueue.size()), GENERATE_CONTEXT(), LogLevel::DEBUG);
        lock.unlock();
        _condVar.notify_one();
    }
}

void BasicServer::endCommunication(const bool force)
{
    if (force)
    {
        _forceEnd = true;
        logger().log("Forcefully ending communications...", GENERATE_CONTEXT());
    }
    else
    {
        _forceEnd = false;
        logger().log("Gracefully ending communications...", GENERATE_CONTEXT());
    }

    _endComms = true;
}

const string BasicServer::defaultLogFileName = "transmitter.log";

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

void BasicServer::senderThreadFunc()
{
    static size_t totalSent = 0;

    logger().log("Sender thread started", GENERATE_CONTEXT(), LogLevel::DEBUG);
    _threadStarted = true;
    _condVar.notify_one();

    while (true)
    {
        logger().log("Waiting for notification...", GENERATE_CONTEXT(), LogLevel::DEBUG);
        unique_lock<mutex> lock{ _mutex };
        while (_condVar.wait_for(lock, std::chrono::milliseconds(100),
            [&]
            {
                return _notified;
            }) == false);
        logger().log("Woken up, sending message batch...", GENERATE_CONTEXT(), LogLevel::DEBUG);

        if (_endComms && _forceEnd)
        {
            logger().log("Communications ended forcefully", GENERATE_CONTEXT(),
                LogLevel::DEBUG);
            lock.unlock();
            break;
        }

        _notified = false;
        queue<string> sendQueue;
        swap(_msgQueue, sendQueue);
        lock.unlock();
        const auto batchSize = sendQueue.size();
        totalSent += batchSize;

        while (!sendQueue.empty())
        {
            std::cout << sendQueue.front() << std::endl;
            sendQueue.pop();
        }
        logger().log("Sent message batch of size: " + to_string(batchSize)
            + " (total sent = " + to_string(totalSent) + ")", GENERATE_CONTEXT(),
            LogLevel::DEBUG);

        if (_endComms)
        {
            logger().log("Communications ended gracefully", GENERATE_CONTEXT(),
                LogLevel::DEBUG);
            break;
        }
    }

    logger().log("Sender thread stopped", GENERATE_CONTEXT(), LogLevel::DEBUG);
}