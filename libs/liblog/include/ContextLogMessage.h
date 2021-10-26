#ifndef CONTEXT_LOG_MESSAGE_H
#define CONTEXT_LOG_MESSAGE_H

#include "LogContext.h"
#include "BasicLogMessage.h"
#include <string>

class ContextLogMessage : public BasicLogMessage
{
public:
    ContextLogMessage(const std::string& content,
        const LogContext& context,
        const LogLevel level = LogLevel::INFO,
        const Timepoint& timestamp = std::chrono::system_clock::now());
    
    LogContext getContext() const noexcept { return _context; }
    explicit operator std::string() const override;
private:
    const LogContext _context;
};

#endif