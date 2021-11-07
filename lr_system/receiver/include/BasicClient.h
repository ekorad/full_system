#include "DefaultLoggable.h"
#include <string>

class BasicClient : public DefaultLoggable<BasicClient>
{
public:
    BasicClient();
    ~BasicClient();

    void connect(const std::string& ipAddr = defaultIpAddr,
        const int port = defaultPort);
    void close();

private:
    bool closeSocket();
    void receive();

    static constexpr int defaultPort = 1337;
    static const std::string defaultIpAddr;
    static const std::string defaultLogFileName;

    unsigned _fdSocket = -1;
};