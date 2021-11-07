#include <iostream>
#include "BasicServer.h"
#include "CustomDataMessage.h"

#include "ert_step.h"
#include "system_transmitter.h"

using namespace std;

int main(int argc, char* argv[])
{
    size_t numSamples = 5000000;
    unsigned port = 1337;
    ofstream logOut{ "transmitter_main.log" };
    Logger<NonContext_t> logger{ logOut };

    if (argc > 1)
    {
        numSamples = stoul(argv[1]);
        if (argc == 3)
        {
            port = stoi(argv[2]);
        }

        if (argc > 3)
        {
            cerr << "Too many arguments" << endl;
            return 1;
        }
    }

    setMaxSamples(numSamples);
    logger.log("Set model sample count to: " + to_string(numSamples), GENERATE_CONTEXT(),
        LogLevel::DEBUG);

    system_transmitter_initialize();
    logger.log("Initialized system model", GENERATE_CONTEXT(), LogLevel::INFO);

    try
    {
        BasicServer server;

        server.host(port);

        logger.log("Connection up and running, processing and sending samples...",
            GENERATE_CONTEXT(), LogLevel::INFO);

        while ((rtmGetErrorStatus(system_transmitter_M) == (NULL)) &&
            !rtmGetStopRequested(system_transmitter_M)) {
            auto msg = rt_OneStep();
            server.send(msg);
        }

        logger.log("Processing and sending over, requesting graceful shutdown...", GENERATE_CONTEXT(),
            LogLevel::INFO);

        server.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    system_transmitter_terminate();
    logger.log("Shutdown system model", GENERATE_CONTEXT(), LogLevel::INFO);

    return 0;
}