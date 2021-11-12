#pragma once

#include "web_serv_http_request.h"

#include <string_view>
#include <map>
#include <algorithm>

class Stats {
public:
    Stats()
    {
        methodCount = { 
            {"GET", 0},
            {"PUT", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"UNKNOWN", 0},
        };

        uriCount = {
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0},
            {"unknown", 0},
        };
 
    }

    void AddMethod(std::string_view method)
    {
        auto pos = methodCount.find(method);
        if (pos == methodCount.end()) {
            methodCount["UNKNOWN"]++;
            return;
        }
        
        methodCount[method]++;
    }

    void AddUri(std::string_view uri)
    {
        auto pos = uriCount.find(uri);
        if (pos == uriCount.end()) {
            uriCount["unknown"]++;
            return;
        }
        
        uriCount[uri]++;
    }

    const map<std::string_view, int>& GetMethodStats() const
    {
        return methodCount;
    }

    const map<std::string_view, int>& GetUriStats() const
    {
        return uriCount;
    }


private:
    std::map<std::string_view, int> methodCount;
    std::map<std::string_view, int> uriCount;
};

std::string_view ReadToken(std::string_view& source)
{
    auto space_pos = source.find(' ');
    auto toReturn = source.substr(0, space_pos);
    source.remove_prefix(space_pos + 1);
    return toReturn;
}

// line - string_view to string like "GET /order HTTP/1.1"
HttpRequest ParseRequest(std::string_view line)
{
    // skip empty space before first character
    line.remove_prefix(line.find_first_not_of(' '));

    HttpRequest result;
    result.method = ReadToken(line);
    result.uri = ReadToken(line);
    result.protocol = ReadToken(line);

    return result;
}



