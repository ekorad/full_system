#include <iostream>
#include <fstream>
#include <server/BasicServer.h>

using namespace std;

int main()
{
    try
    {
        BasicServer sv;
        sv.awaitConnection();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}