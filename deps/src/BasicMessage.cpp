#include "BasicMessage.h"

using std::ostream;
using std::string;

ostream& operator<<(ostream& os, const BasicMessage& msg)
{
    os << string(msg);
    return os;
}

BasicMessage::BasicMessage(const string& content)
    : _content{ content } {}