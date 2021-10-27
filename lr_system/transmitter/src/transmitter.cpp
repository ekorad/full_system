#include <iostream>
#include <fstream>
#include "BasicServer.h"

using namespace std;

int main()
{
    try
    {
        BasicServer server;
        server.host();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}