#include "LogContext.h"

using std::string;
using std::optional;
using std::size_t;
using std::nullopt;

LogContext::LogContext(const string& clsName, const string& funcName,
    const optional<string> fileNameOpt, const optional<size_t> lineNumOpt)
    : _funcName{ funcName }, _fileNameOpt{ fileNameOpt }, _lineNumOpt{ lineNumOpt },
    _clsNameOpt{ clsName } {}

LogContext::LogContext(const string& funcName, const optional<string> fileNameOpt,
    const optional<size_t> lineNumOpt)
    : _funcName{ funcName }, _fileNameOpt{ fileNameOpt }, _lineNumOpt{ lineNumOpt },
    _clsNameOpt{ nullopt } {}

LogContext::operator string() const
{
    string retVal;

    if (_clsNameOpt.has_value())
    {
        retVal = _clsNameOpt.value() + "::";
    }

    retVal += _funcName;

    return retVal;
}
