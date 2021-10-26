#include "ContextLogMessage.h"

using std::string;

ContextLogMessage::ContextLogMessage(const std::string& content,
        const LogContext& context, const LogLevel level,
        const Timepoint& timestamp)
    : BasicLogMessage(content, level, timestamp),
    _context{ context } {}

ContextLogMessage::operator string() const
{
    return ("[" + timestampToString(getTimestamp()) + "]["
        + levelToShortString(getLogLevel()) + "]["
        + static_cast<string>(_context) + "] "
        + getMessageContent());
}