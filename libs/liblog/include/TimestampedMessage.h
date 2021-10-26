#ifndef TIMESTAMPED_MESSAGE_H
#define TIMESTAMPED_MESSAGE_H

#include "BasicMessage.h"
#include <chrono>

class TimestampedMessage : public BasicMessage
{
public:
    using Timepoint = decltype(std::chrono::system_clock::now());

    TimestampedMessage(const std::string& content,
        const Timepoint& timestamp = std::chrono::system_clock::now());

    Timepoint getTimestamp() const;
    explicit operator std::string() const override;

protected:
    std::string timestampToString(const Timepoint& timestamp) const;

private:
    const Timepoint _timestamp;
};

#endif