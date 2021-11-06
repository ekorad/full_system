#include "LogLevel.h"
#include <stdexcept>

using std::string;
using std::runtime_error;

string logLevelToString(const LogLevel level)
{
    switch (level)
    {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            throw runtime_error("Invalid log level");
    }
}