#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

#include <string>

enum class LogLevel
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
};

std::string logLevelToString(const LogLevel level);

#endif