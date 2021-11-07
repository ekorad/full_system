#include "Logger.h"
#include <algorithm>

#define GENERATE_CONTEXT_FOR(x) LogContext(x, LOG_CONTEXT_PARAMS)

Logger::Logger(const std::optional<std::string> target, const bool enabled)
	: _target{ target }, _enabled{ enabled }
{
	std::unique_lock<std::mutex> lock{ staticMutex };
	registeredLoggers.push_back(this);
	lock.unlock();

	log("Registered logger", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
}

Logger::~Logger()
{
	std::unique_lock<std::mutex> lock{ staticMutex };
	auto loggerIt = std::remove(registeredLoggers.begin(), registeredLoggers.end(), this);
	const auto loggersLeft = registeredLoggers.size();
	lock.unlock();

	log("Unregistered logger", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);

	if (loggersLeft == 1)
	{
		log("Logger thread shutdown", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
		lock.lock();
		loggerThreadShutdown = true;
		lock.unlock();
		staticCondVar.notify_one();

		if (loggerThread.has_value())
		{
			loggerThread.value().join();
		}
	}

	lock.lock();
	registeredLoggers.erase(loggerIt);
}

void Logger::init()
{
	std::unique_lock<std::mutex> lock{ staticMutex };

	if (!loggerThread.has_value())
	{
		try
		{
			loggerThread = std::thread{ loggerThreadFunc };
		}
		catch(const std::system_error& error)
		{
			lock.unlock();
			throw std::system_error{ error.code().value(), std::system_category(),
				"Could not start logger thread" };
		}
	}
}

void Logger::enableAllLoggers(const bool enabled)
{
	for (auto logger : registeredLoggers)
	{
		if (logger)
		{
			logger->enable(enabled);
		}
		else
		{
			throw std::runtime_error("Logger vector corrupted");
		}
	}
}

void Logger::setMinimumLogLevelAll(const LogLevel level)
{
	for (auto logger : registeredLoggers)
	{
		if (logger)
		{
			logger->setMinimumLogLevel(level);
		}
		else
		{
			throw std::runtime_error("Logger vector corrupted");
		}
	}
}

void Logger::setLogFileName(const std::string& fileName)
{
	if (loggerThread.has_value())
	{
		throw std::runtime_error("File name cannot be changed after"
			" the logger thread has been started");
	}

	if (fileName.empty())
	{
		throw std::runtime_error("File name cannot be empty");
	}

	std::unique_lock<std::mutex> lock{ staticMutex };
	logFileName = fileName;
}

std::string Logger::getLogFileName() noexcept
{
	std::unique_lock<std::mutex> lock{ staticMutex };
	auto fileName = logFileName;
	lock.unlock();

	return fileName;
}

std::optional<std::string> Logger::getTargetName() const noexcept
{
	return _target;
}

bool Logger::enabled() const noexcept
{
	return _enabled;
}

void Logger::enable(const bool enabled) noexcept
{
	if (enabled)
	{
		log("Enabled logger", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
	}
	else
	{
		log("Disabled logger", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
	}
	_enabled = enabled;
}

LogLevel Logger::getMinimumLogLevel() const noexcept
{
	const int intLevel = _minLogLevel;
	return static_cast<LogLevel>(intLevel);
}

void Logger::setMinimumLogLevel(const LogLevel level)
{
	if (level > LogLevel::ERROR)
	{
		throw std::runtime_error("Invalid log level");
	}

	const int intLevel = static_cast<int>(level);
	log("Minimum log level set to: " + std::to_string(intLevel) + " (" + logLevelToString(level)
		+ ")", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);

	_minLogLevel = intLevel;
}

void Logger::log(const std::string& logMessage, const std::optional<LogContext> logContext,
	const LogLevel level) const
{
	if (!_enabled)
	{
		return;
	}

	const int intMinLevel = static_cast<int>(_minLogLevel);
	if (static_cast<int>(level) < intMinLevel)
	{
		return;
	}

	std::unique_lock<std::mutex> lock{ staticMutex };
	if (logContext.has_value())
	{
		auto context = logContext.value();
		if (_target.has_value())
		{
			auto predefTargetName = context.getTargetName();

			if (predefTargetName.has_value())
			{
				context.setTargetName(_target.value() + "::" + predefTargetName.value());
			}
			else
			{
				context.setTargetName(_target.value());
			}
		}
		logQueue.push(std::make_unique<ContextLogMessage>(ContextLogMessage{ logMessage,
			context, level }));
	}
	else
	{
		logQueue.push(std::make_unique<BasicLogMessage>(BasicLogMessage{ logMessage, level }));
	}
	loggerThreadNotified = true;
	lock.unlock();

	staticCondVar.notify_one();
}

void Logger::loggerThreadFunc()
{
	static constexpr auto waitPeriod = std::chrono::milliseconds(100);
	static bool shutdownInProgress = false;

	logOut.open(logFileName);

	while (true)
	{
		std::unique_lock<std::mutex> lock{ staticMutex };
		staticCondVar.wait_for(lock, waitPeriod, 
			[&] {
				return static_cast<bool>(loggerThreadNotified);
			});

		shutdownInProgress = loggerThreadShutdown;

		std::queue<std::unique_ptr<BasicMessage>> tmpQueue;
		std::swap(tmpQueue, logQueue);
		lock.unlock();

		if (!tmpQueue.empty())
		{
			while (!tmpQueue.empty())
			{
				auto front = std::move(tmpQueue.front());
				tmpQueue.pop();

				if (front)
				{
					if (!alwaysFlush)
					{
						std::lock_guard<std::mutex> tmpLock{ staticMutex };
						logOut << *front.get() << std::endl;
					}
					else
					{
						std::string msg = static_cast<std::string>(*front.get()) + "\n";
						logOut << msg;
					}
				}
				else
				{
					throw std::runtime_error("Log queue corrupted");
				}
			}
		}
		else if (shutdownInProgress)
		{
			break;
		}
	}
};

void Logger::enableFlushing(const bool enabled) noexcept
{
	if (enabled)
	{
		log("Flushing enabled", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
	}
	else
	{
		log("Flushing disabled", GENERATE_CONTEXT_FOR(clsName), LogLevel::DEBUG);
	}
	alwaysFlush = enabled;
}

bool Logger::flushingEnabled() const noexcept
{
	return alwaysFlush;
}

const std::string Logger::clsName{ "Logger" };
std::string Logger::logFileName{ "out.log" };
std::ofstream Logger::logOut;
std::condition_variable Logger::staticCondVar;
std::mutex Logger::staticMutex;
std::optional<std::thread> Logger::loggerThread;
std::queue<std::unique_ptr<BasicMessage>> Logger::logQueue;
std::vector<Logger*> Logger::registeredLoggers;
std::atomic_bool Logger::loggerThreadNotified{ false };
std::mutex Logger::flushMutex;
std::atomic_bool Logger::alwaysFlush{ false };
bool Logger::loggerThreadShutdown{ false };