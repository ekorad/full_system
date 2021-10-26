#include "StringUtils.h"

using std::vector;
using std::string;

vector<string> StringUtils::splitString(const string& str, const string& delim)
{
    vector<string> tokens;
    auto tokensStr = str;
    decltype(str.length()) foundIndex;

    while ((foundIndex = tokensStr.find(delim)) != string::npos)
    {
        tokens.push_back(tokensStr.substr(0, foundIndex));
        tokensStr = tokensStr.substr(foundIndex + delim.length());
    }

    tokens.push_back(tokensStr);

    return tokens;
}