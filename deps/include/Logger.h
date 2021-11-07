#ifndef LOGGER_H
#define LOGGER_H

#include "ContextLogMessage.h"
#include <optional>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>
#include <vector>
#include <memory>
#include <fstream>

class Logger
{
public:
	Logger(const std::optional<std::string> target = std::nullopt,
		const bool enabled = true);
	virtual ~Logger();

    static void init();
	static void enableAllLoggers(const bool enabled = true);
	static void setMinimumLogLevelAll(const LogLevel level);
    static void setLogFileName(const std::string& fileName);
    static std::string getLogFileName() noexcept;

	std::optional<std::string> getTargetName() const noexcept;

	bool enabled() const noexcept;
	void enable(const bool enabled = true) noexcept;
	LogLevel getMinimumLogLevel() const noexcept;
	void setMinimumLogLevel(const LogLevel level);
	void enableFlushing(const bool enabled = true) noexcept;
	bool flushingEnabled() const noexcept;

	void log(const std::string& logMessage,
		const std::optional<LogContext> logContext = std::nullopt,
		const LogLevel level = LogLevel::INFO) const;

private:
	static void loggerThreadFunc();

	static const std::string clsName;

    static std::string logFileName;
	static std::ofstream logOut;
	static std::condition_variable staticCondVar;
	static std::mutex staticMutex;
	static std::optional<std::thread> loggerThread;
	static std::queue<std::unique_ptr<BasicMessage>> logQueue;
	static std::vector<Logger*> registeredLoggers;
	static std::atomic_bool loggerThreadNotified;
	static std::mutex flushMutex;
	static std::atomic_bool alwaysFlush;
	static bool loggerThreadShutdown;

	const std::optional<std::string> _target;
	std::atomic_bool _enabled;
	std::atomic_int _minLogLevel = static_cast<int>(LogLevel::DEBUG);
};

#endif