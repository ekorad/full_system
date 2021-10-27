#ifndef BASIC_SERVER_H
#define BASIC_SERVER_H

#include "DefaultLoggable.h"
#include <fstream>
#include <netinet/in.h>

class BasicServer : public DefaultLoggable<BasicServer>
{
public:
    BasicServer(const int port = defaultPort);
    ~BasicServer();

    void awaitConnection();
    void close();
    void disconnectClient();

private:
    static constexpr int defaultPort = 1337;

    bool closeServerSocket();
    bool disconnect();

    sockaddr_in _addrServer;
    sockaddr_in _addrClient;
    int _fdServerSock = -1;
    int _fdClientSock = -1;
    int _port = defaultPort;
};

#endif