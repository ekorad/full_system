#ifndef BASIC_SERVER_H
#define BASIC_SERVER_H

#include "DefaultLoggable.h"
#include <fstream>
#include <netinet/in.h>

class BasicServer : public DefaultLoggable<BasicServer>
{
public:
    BasicServer();
    ~BasicServer();

    void host(const unsigned port = defaultPort);
    void close();
    void disconnectClient();

private:
    static constexpr unsigned defaultPort = 1337;
    static const std::string defaultLogFileName;

    bool closeServerSocket();
    bool disconnect();

    sockaddr_in _addrClient;
    int _fdServerSock = -1;
    int _fdClientSock = -1;
};

#endif