#include "TimestampedMessage.h"
#include <system_error>

using std::system_category;
using std::system_error;
using std::string;
using std::to_string;
using std::ostream;

TimestampedMessage::TimestampedMessage(const string& content,
    const Timepoint& timestamp)
    : BasicMessage(content),
    _timestamp{ timestamp } {}

TimestampedMessage::Timepoint TimestampedMessage::getTimestamp() const
{
    return _timestamp;
}

TimestampedMessage::operator string() const
{
    return ("[" + timestampToString(getTimestamp()) + "] "
        + getMessageContent()); 
}

string TimestampedMessage::timestampToString(const Timepoint& timestamp) const
{
    constexpr size_t microsPrecision = 5;
    constexpr size_t microsPerSec = 1000000;
    constexpr size_t bufSize = 1024;
    char buf[bufSize];

    const std::time_t timeT = std::chrono::system_clock::to_time_t(timestamp);
    const tm* tmT = localtime(&timeT);

    if (strftime(buf, bufSize, "%F %T", tmT) == 0)
    {
        throw system_error(errno, system_category(), "Could not format timestamp");
    }

    string strTimestamp{ buf };

    const auto timestampInMicros = std::chrono::time_point_cast<std::chrono::microseconds>(timestamp);
    const auto micros = timestampInMicros.time_since_epoch().count();
    const auto microsRem = (micros % microsPerSec);

    string strMicrosRem = to_string(microsRem);

    if (strMicrosRem.length() > microsPrecision)
    {
        strMicrosRem = strMicrosRem.substr(0, microsPrecision);
    }
    else
    {
        auto precisionDif = microsPrecision - strMicrosRem.length();
        strMicrosRem = string(precisionDif, '0') + strMicrosRem;
    }

    strTimestamp += "." + strMicrosRem;

    return strTimestamp;
}