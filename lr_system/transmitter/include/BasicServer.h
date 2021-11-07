#ifndef BASIC_SERVER_H
#define BASIC_SERVER_H

#include "DataTransferObject.h"
#include "Logger.h"
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <netinet/in.h>

class BasicServer
{
public:
    BasicServer();
    ~BasicServer();

    void host(const unsigned port = defaultPort);
    void close();
    void disconnectClient();

    void send(const ISerializable& message);

private:
    static constexpr unsigned defaultPort = 1337;
    static const std::string defaultLogFileName;

    bool closeServerSocket();
    bool disconnect();
    void shutdownComms(const bool force = false);

    void senderThreadFunc();

    Logger _logger{ "BasicServer" };

    sockaddr_in _addrClient;
    int _fdServerSock = -1;
    int _fdClientSock = -1;

    std::thread _senderThread;
    std::mutex _mutex;
    std::condition_variable _condVar;
    std::queue<DataTransferObject> _msgQueue;
    bool _notified = false;
    std::atomic_bool _shutdownComms = false;
    std::atomic_bool _forceShutdown = false;
    std::atomic_bool _threadStarted = false;
};

#endif