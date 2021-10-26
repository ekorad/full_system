#include "Utils.h"
#include <cxxabi.h>

using std::optional;
using std::nullopt;
using std::string;

optional<string> Utils::demangleTypeName(const string& mangledName)
{
    char* demangledName = abi::__cxa_demangle(mangledName.c_str(), nullptr,
        nullptr, nullptr);

    if (demangledName)
    {
        return optional<string>(demangledName);
        free(demangledName);
    }

    return nullopt;
}