#ifndef LOG_CONTEXT_H
#define LOG_CONTEXT_H

#include <string>
#include <optional>

#define LOG_CONTEXT_PARAMS      __func__, __FILE__, __LINE__
#define GENERATE_CONTEXT()      LogContext(LOG_CONTEXT_PARAMS)

class LogContext
{
public:
    LogContext() {}
    LogContext(const std::string& clsName, const std::string& funcName,
        const std::optional<std::string> fileNameOpt = std::nullopt,
        const std::optional<std::size_t> lineNumOpt = std::nullopt);
    LogContext(const std::string& funcName,
        const std::optional<std::string> fileNameOpt = std::nullopt,
        const std::optional<std::size_t> lineNumOpt = std::nullopt);

    std::string getFunctionName() const noexcept { return _funcName; }
    std::optional<std::string> getFileName() const noexcept { return _fileNameOpt; }
    std::optional<std::size_t> getLineNumber() const noexcept { return _lineNumOpt; }
    std::optional<std::string> getTargetName() const noexcept { return _targetNameOpt; }

    void setFunctionName(const std::string& funcName) noexcept { _funcName = funcName; }
    void setFileName(const std::string& fileName) { _fileNameOpt = fileName; }
    void setLineNumber(const std::size_t lineNum) { _lineNumOpt = lineNum; }
    void setTargetName(const std::string& targetName) { _targetNameOpt = targetName; }

    void clearFileName() { _fileNameOpt.reset(); }
    void clearLineNumber() { _lineNumOpt.reset(); }
    void clearClassName() { _targetNameOpt.reset(); }

    explicit operator std::string() const;
private:
    std::string _funcName;
    std::optional<std::string> _targetNameOpt;
    std::optional<std::string> _fileNameOpt;
    std::optional<std::size_t> _lineNumOpt;
};

#endif