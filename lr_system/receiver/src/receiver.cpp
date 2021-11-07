#include <iostream>
#include <string>

#include "BasicClient.h"

using namespace std;

int main()
{
    try
    {
        BasicClient client;
        client.connect();
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "ss" << '\n';
    }

    return 0;
}