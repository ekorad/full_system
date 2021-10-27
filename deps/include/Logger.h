#include "ContextLogMessage.h"
#include "Utils.h"
#include "ILogger.h"
#include <ostream>
#include <fstream>
#include <string>
#include <atomic>
#include <typeinfo>
#include <iostream>
#include <memory>
#include <cxxabi.h>
#include <stdlib.h>

using std::ostream;
using std::ofstream;
using std::string;
using std::endl;
using std::is_same;
using std::atomic_bool;
using std::atomic_int;
using std::mutex;
using std::lock_guard;
using std::cerr;
using std::vector;
using std::optional;
using std::nullopt;
using std::make_unique;

struct NonContext_t final {};

template <typename T>
class Logger : public ILogger
{
public:
    Logger(ostream& outputStream, const bool enabled = true);

    void log(const string& logMessage,
        const optional<LogContext> logContext = nullopt,
        const LogLevel level = LogLevel::INFO) override;

    void setMinimumLogLevel(const LogLevel level) noexcept override;
    void setPerformanceMode(const bool preferPerformance = true) noexcept;
    void allowInterleaving(const bool allow = true) noexcept;
    void enableFlushing(const bool enabled = true) noexcept;
    void enable(const bool enabled = true) noexcept override;

    LogLevel getMinimumLogLevel() const noexcept;
    bool performancePreferred() const noexcept;
    bool interleavingAllowed() const noexcept;
    bool flushingEnabled() const noexcept;
    bool enabled() const noexcept;

private:
    mutable mutex _interleaveMutex;

    ostream& _os;

    atomic_bool _enabled;
    atomic_bool _flushing = true;
    atomic_bool _interleavingAllowed = false;
    atomic_int _minLogLevel = static_cast<int>(LogLevel::DEBUG);
};

template <typename T>
Logger<T>::Logger(ostream& outputStream, const bool enabled)
    : _os{ outputStream }, _enabled{ enabled }
{
    log("Registered logger", GENERATE_CONTEXT());
}

template <typename T>
void Logger<T>::log(const string& logMessage,
    const optional<LogContext> logContext, const LogLevel level)
{
    if (!_enabled)
    {
        return;
    }

    if (static_cast<int>(level) < _minLogLevel)
    {
        return;
    }

    optional<LogContext> newContextOpt = logContext;

    if (newContextOpt.has_value()
        && (is_same<T, NonContext_t>::value == false)
        && (!newContextOpt.value().getClassName().has_value()))
    {
        const string mangledName = typeid(T).name();
        optional<string> demangledNameOpt = Utils::demangleTypeName(mangledName);

        if (demangledNameOpt.has_value())
        {
            newContextOpt.value().setClassName(demangledNameOpt.value());
        }
        else
        {
            log("Could not demangle \"" + mangledName + "\"", nullopt,
                LogLevel::WARNING);
        }
    }

    const auto logPtr = (newContextOpt.has_value()
        ? make_unique<ContextLogMessage>(ContextLogMessage{ logMessage, newContextOpt.value(), level })
        : make_unique<BasicLogMessage>(BasicLogMessage{ logMessage, level }));

    if (!_interleavingAllowed && _flushing)
    {
        lock_guard<mutex> lock{ _interleaveMutex };
        _os << static_cast<string>(*logPtr.get()) << endl;
    }
    else
    {
        string buffer = static_cast<string>(*logPtr.get()) + "\n";
        _os << buffer;
    }
}

template <typename T>
void Logger<T>::setMinimumLogLevel(const LogLevel level) noexcept
{
    _minLogLevel = static_cast<int>(level);
}

template <typename T>
void Logger<T>::setPerformanceMode(const bool preferPerformance) noexcept
{
    _flushing = !preferPerformance;
    _interleavingAllowed = !preferPerformance;
}

template <typename T>
void Logger<T>::enable(const bool enabled) noexcept
{
    _enabled = enabled;
}

template <typename T>
void Logger<T>::enableFlushing(const bool enabled) noexcept
{
    _flushing = enabled;
}

template <typename T>
void Logger<T>::allowInterleaving(const bool allow) noexcept
{
    _interleavingAllowed = allow;
}

template <typename T>
LogLevel Logger<T>::getMinimumLogLevel() const noexcept
{
    int level = static_cast<int>(_minLogLevel);
    return static_cast<LogLevel>(level);
}

template <typename T>
bool Logger<T>::performancePreferred() const noexcept
{
    return (!_flushing && !_interleavingAllowed);
}

template <typename T>
bool Logger<T>::enabled() const noexcept
{
    return _enabled;
}

template <typename T>
bool Logger<T>::flushingEnabled() const noexcept
{
    return _flushing;
}

template <typename T>
bool Logger<T>::interleavingAllowed() const noexcept
{
    return _interleavingAllowed;
}