#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <optional>

class Utils
{
public:
    Utils() = delete;
    Utils(const Utils&) = delete;
    Utils(Utils&&) = delete;
    Utils& operator=(const Utils&) = delete;
    Utils& operator=(Utils&&) = delete;

    static std::optional<std::string> demangleTypeName(const std::string& mangledName);
};

#endif