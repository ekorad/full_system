#ifndef BASIC_SERVER_H
#define BASIC_SERVER_H

#include <fstream>
#include <log/DefaultLoggable.h>
#include <netinet/in.h>

class BasicServer : public DefaultLoggable<BasicServer>
{
public:
    BasicServer(const int port = defaultPort);
    ~BasicServer();

    void awaitConnection();

    int getPortNumber() const noexcept { return _port; }
    void setPortNumber(const int port) noexcept { _port = port; } 
    void resetPortNumber() noexcept { setPortNumber(defaultPort); }
private:
    static constexpr int defaultPort = 1337;

    sockaddr_in _addrServer;
    sockaddr_in _addrClient;
    int _fdServerSock;
    int _fdClientSock;
    int _port;
};

#endif