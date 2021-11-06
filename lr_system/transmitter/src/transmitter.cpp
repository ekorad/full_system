#include <iostream>
#include "BasicServer.h"
#include "CustomDataMessage.h"

using namespace std;

int main()
{
    try
    {
        BasicServer server;
        // ILogger::allLoggersSetMinimumLogLevel(LogLevel::INFO);

        server.host();

        for (int i = 0; i < 10000; i++)
        {
            server.send(CustomDataMessage{i + 1, i + 2, i + 3});
        }

        server.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}