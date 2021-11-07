#ifndef I_LOGGER_H
#define I_LOGGER_H

#include "ContextLogMessage.h"
#include <vector>
#include <mutex>
#include <optional>

class ILogger
{
public:
    ILogger();
    virtual ~ILogger();

    virtual void enable(const bool enabled = true) noexcept = 0;
    virtual void setMinimumLogLevel(const LogLevel level) noexcept = 0;

    virtual void log(const std::string& logMessage,
        const std::optional<LogContext> logContext = std::nullopt,
        const LogLevel level = LogLevel::INFO) = 0;

    static void enableAllLoggers(const bool enabled = true);
    static void allLoggersSetMinimumLogLevel(const LogLevel level);
    static std::size_t getRegisteredLoggers() noexcept;

private:
    static std::vector<ILogger*> loggers;
    static std::mutex loggersMutex;
};

#endif