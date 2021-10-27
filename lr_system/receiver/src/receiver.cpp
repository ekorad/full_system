#include <iostream>
#include <string>

using namespace std;

/*
int connectToServer(const string& ipAddr)
{
    if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("socket");
        return -1;
    }

    sv_addr.sin_family = AF_INET;
    sv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, ipAddr.c_str(), &sv_addr.sin_addr) <= 0) 
    {
        perror("inet_pton");
        return -1;
    }

    if (connect(client_sock_fd, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) < 0)
    {
        perror("connect");
        return -1;
    }

    dbgout << setprecision(17);

    return 0;
}*/
class BasicClient
{
public:
    BasicClient(const std::string& ipAddr = defaultIpAddr,
        const int port = defaultPort);
    
    void connect();
private:
    static constexpr int defaultPort = 1337;
    static const std::string defaultIpAddr;
};

const string BasicClient::defaultIpAddr = "127.0.0.1";

int main()
{

    return 0;
}