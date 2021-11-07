#include "BasicClient.h"
#include <system_error>
#include <arpa/inet.h>
#include <unistd.h>

using std::system_error;
using std::system_category;
using std::string;
using std::to_string;

BasicClient::BasicClient()
{
    _fdSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_fdSocket == -1)
    {
        const auto error = system_error(errno, system_category(), "Could not create client socket");
        _logger.log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        _logger.log("Initialized client socket with descriptor: " + to_string(_fdSocket),
            GENERATE_CONTEXT(), LogLevel::DEBUG);
    }

    _logger.log("Client initialization successful", GENERATE_CONTEXT());
}

BasicClient::~BasicClient()
{
    closeSocket();

    _logger.log("Client terminated", GENERATE_CONTEXT());
}

void BasicClient::connect(const string& ipAddr, const int port)
{
    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(port);

    if (inet_pton(AF_INET, ipAddr.c_str(), &addrServer.sin_addr) <= 0) 
    {
        const auto error = system_error(errno, system_category(),
            "Could not convert IP address string " + ipAddr + " to binary form");
        _logger.log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }

    _logger.log("Attempting connection to server with IP address "
        + ipAddr + " on port " + to_string(port) + "...", GENERATE_CONTEXT());

    if (::connect(_fdSocket, (struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
    {
        const auto error = system_error(errno, system_category(),
            "Could not connect to server");
        _logger.log(error.what(), GENERATE_CONTEXT(), LogLevel::ERROR);
        throw error;
    }
    else
    {
        _logger.log("Connection to server established", GENERATE_CONTEXT());
    }

    receive();
}

void BasicClient::close()
{
    if (closeSocket() == false)
    {
        _logger.log("Client already closed", GENERATE_CONTEXT());
    }
}

const string BasicClient::defaultIpAddr = "127.0.0.1";
const string BasicClient::defaultLogFileName = "receiver.log";

bool BasicClient::closeSocket()
{
    if (_fdSocket != -1)
    {
        int fd = _fdSocket;
        ::close(_fdSocket);
        _fdSocket = -1;

        _logger.log("Closed client socket (descriptor = " + to_string(fd) + ")",
            GENERATE_CONTEXT());

        return true;
    }

    return false;
}

#include <iostream>
using namespace std;

void BasicClient::receive()
{
    double dblBuf[3];
    while (read(_fdSocket, dblBuf, sizeof(dblBuf)) > 0)
    {
        // cout << dblBuf[0] << " " << dblBuf[1] << " " << dblBuf[2] << endl;
    }
}