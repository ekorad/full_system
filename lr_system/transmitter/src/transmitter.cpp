#include <iostream>
#include "BasicServer.h"

using namespace std;

int main()
{
    try
    {
        BasicServer server;
        server.host();

        /*for (int i = 0; i < 10000; i++)
        {
            server.send("Message " + to_string(i + 1));
        }

        this_thread::sleep_for(std::chrono::seconds(1));
        server.send("last msg");*/

        server.send("first message");

        while (true);
        // server.endTransmission();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}