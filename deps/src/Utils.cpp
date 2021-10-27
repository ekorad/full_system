#include "Utils.h"
#include <cxxabi.h>
#include <arpa/inet.h>

using std::optional;
using std::nullopt;
using std::string;
using std::to_string;

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

optional<string> Utils::convertIPAddressToString(const in_addr& addr)
{
    char ipAddr[INET_ADDRSTRLEN];
    string ipAddrStr;
    const char* retVal = inet_ntop(AF_INET, &(addr), ipAddr, INET_ADDRSTRLEN);

    if (retVal == nullptr)
    {
        return nullopt;
    }
    else
    {
        return ipAddrStr;
    }
}