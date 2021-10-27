#include "ILogger.h"
#include <algorithm>

using std::lock_guard;
using std::mutex;
using std::vector;
using std::remove;

vector<ILogger*> ILogger::loggers;
mutex ILogger::loggersMutex;

ILogger::ILogger()
{
    lock_guard<mutex> lock{ loggersMutex };
    loggers.push_back(this);
}

ILogger::~ILogger()
{
    lock_guard<mutex> lock{ loggersMutex };
    remove(loggers.begin(), loggers.end(), this);
}

void ILogger::enableAllLoggers(const bool enabled)
{
    lock_guard<mutex> lock{ loggersMutex };
    for (auto& pLogger : loggers)
    {
        if (pLogger)
        {
            pLogger->enable(enabled);
        }
    }
}

void ILogger::allLoggersSetMinimumLogLevel(const LogLevel level)
{
    lock_guard<mutex> lock{ loggersMutex };
    for (auto& pLogger : loggers)
    {
        if (pLogger)
        {
            pLogger->setMinimumLogLevel(level);
        }
    }
}