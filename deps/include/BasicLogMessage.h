#ifndef BASIC_LOG_MESSAGE_H
#define BASIC_LOG_MESSAGE_H

#include "TimestampedMessage.h"
#include "LogLevel.h"

class BasicLogMessage : public TimestampedMessage
{
public:
    BasicLogMessage(const std::string& content,
        const LogLevel level = LogLevel::INFO,
        const Timepoint& timestamp = std::chrono::system_clock::now());

    LogLevel getLogLevel() const noexcept { return _level; }
    explicit operator std::string() const override;

protected:
    std::string levelToShortString(const LogLevel level) const;

private:
    const LogLevel _level;
};

#endif