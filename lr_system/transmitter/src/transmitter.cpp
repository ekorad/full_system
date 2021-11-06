#include <iostream>
#include "BasicServer.h"
#include "CustomDataMessage.h"

using namespace std;

int main()
{
    try
    {
        BasicServer server;
        server.host();

        for (int i = 0; i < 10000; i++)
        {
            server.send(CustomDataMessage{i + 1, i + 2, i + 3});
        }

        // for (int i = 0; i < 10000; i++)
        // {
        //     server.send("Message " + to_string(i + 1));
        // }

        this_thread::sleep_for(std::chrono::seconds(2));
        // server.send("last msg");

        server.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}