#ifndef DEFAULT_LOGGABLE_H
#define DEFAULT_LOGGABLE_H

#include "Logger.h"

template <typename T>
class DefaultLoggable
{
public:
    DefaultLoggable(const string& fileName = defLogFileName);

    static string getDefaultLogFileName();
    static void setDefaultLogFileName(const string& fileName);

    inline Logger<T>& logger() noexcept { return _logger; }

private:
    static string defLogFileName;
    static mutex staticPropMutex;

    ofstream _logOutStream;
    Logger<T> _logger;
};

template <typename T>
string DefaultLoggable<T>::defLogFileName = "out.log";

template <typename T>
mutex DefaultLoggable<T>::staticPropMutex;

template <typename T>
DefaultLoggable<T>::DefaultLoggable(const string& fileName)
    : _logOutStream{ fileName }, _logger{ _logOutStream } {}

template <typename T>
string DefaultLoggable<T>::getDefaultLogFileName()
{
    string fileName;
    {
        lock_guard<mutex> lock{ staticPropMutex };
        fileName = defLogFileName;
    }
    return fileName;
}

template <typename T>
void DefaultLoggable<T>::setDefaultLogFileName(const string& fileName)
{
    lock_guard<mutex> lock{ staticPropMutex };
    defLogFileName = fileName;
}

#endif