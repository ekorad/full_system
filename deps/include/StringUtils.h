#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

class StringUtils
{
public:
    StringUtils() = delete;
    StringUtils(const StringUtils&) = delete;
    StringUtils(StringUtils&&) = delete;
    StringUtils& operator=(const StringUtils&) = delete;
    StringUtils& operator=(StringUtils&&) = delete;

    static std::vector<std::string> splitString(const std::string& str,
        const std::string& delim);
};

#endif