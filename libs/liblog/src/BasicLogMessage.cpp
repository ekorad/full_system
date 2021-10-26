#include "BasicLogMessage.h"
#include <stdexcept>

using std::string;
using std::runtime_error;

BasicLogMessage::BasicLogMessage(const string& content, const LogLevel level,
    const Timepoint& timestamp)
    : TimestampedMessage(content, timestamp),
    _level{ level } {}

BasicLogMessage::operator string() const
{
    return ("[" + timestampToString(getTimestamp()) + "]["
        + levelToShortString(getLogLevel()) + "] "
        + getMessageContent());
}

string BasicLogMessage::levelToShortString(const LogLevel level) const
{
    switch (level)
    {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            throw runtime_error("Invalid log level");
    }
}