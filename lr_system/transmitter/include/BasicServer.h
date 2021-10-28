#ifndef BASIC_SERVER_H
#define BASIC_SERVER_H

#include "DefaultLoggable.h"
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <netinet/in.h>

class BasicServer : public DefaultLoggable<BasicServer>
{
public:
    BasicServer();
    ~BasicServer();

    void host(const unsigned port = defaultPort);
    void close();
    void disconnectClient();

    void send(const string& message);
    void endCommunication(const bool force = false);

private:
    static constexpr unsigned defaultPort = 1337;
    static const std::string defaultLogFileName;

    bool closeServerSocket();
    bool disconnect();

    void senderThreadFunc();

    sockaddr_in _addrClient;
    int _fdServerSock = -1;
    int _fdClientSock = -1;

    std::thread _senderThread;
    std::mutex _mutex;
    std::condition_variable _condVar;
    std::queue<std::string> _msgQueue;
    bool _notified = false;
    std::atomic_bool _endComms = false;
    std::atomic_bool _forceEnd = false;
    std::atomic_bool _threadStarted = false;
};

#endif