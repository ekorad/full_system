#include "ILogger.h"

using std::lock_guard;
using std::mutex;
using std::shared_ptr;
using std::vector;

vector<shared_ptr<ILogger>> ILogger::loggers;
mutex ILogger::loggersMutex;

ILogger::ILogger()
{
    lock_guard<mutex> lock{ loggersMutex };
    loggers.push_back(shared_ptr<ILogger>{ this });
}

ILogger::~ILogger()
{
    lock_guard<mutex> lock{ loggersMutex };
    auto it = loggers.cbegin() + 1;

    while (it != loggers.cend() - 1)
    {
        const auto& spLogger = *it;
        const auto* pLogger = spLogger.get();

        if (pLogger == nullptr)
        {
            loggers.erase(it);
        }

        else if (pLogger == this)
        {
            loggers.erase(it);
            break;
        }

        it++;
    }
}

void ILogger::enableAllLoggers(const bool enabled)
{
    lock_guard<mutex> lock{ loggersMutex };
    for (auto& spLogger : loggers)
    {
        auto pLogger = spLogger.get();
        if (pLogger)
        {
            pLogger->enable(enabled);
        }
    }
}

void ILogger::allLoggersSetMinimumLogLevel(const LogLevel level)
{
    lock_guard<mutex> lock{ loggersMutex };
    for (auto& spLogger : loggers)
    {
        auto pLogger = spLogger.get();
        if (pLogger)
        {
            pLogger->setMinimumLogLevel(level);
        }
    }
}