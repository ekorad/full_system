#ifndef BASIC_MESSAGE_H
#define BASIC_MESSAGE_H

#include <string>
#include <ostream>

class BasicMessage
{
public:
    BasicMessage(const std::string& content);

    std::string getMessageContent() const noexcept { return _content; }
    virtual explicit operator std::string() const { return getMessageContent(); }

    friend std::ostream& operator<<(std::ostream& os, const BasicMessage& msg);

private:
    const std::string _content;
};

#endif