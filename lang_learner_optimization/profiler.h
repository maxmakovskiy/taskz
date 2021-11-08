#pragma once

#include <chrono>

class LogDuration
{
public:
    explicit LogDuration(const std::string& msg = "")
        : message(msg + ": ")
        , start(std::chrono::steady_clock::now())
    {
    }

    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;
        std::cerr << message
            << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << " us" << std::endl;
    }

private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)
#define UNIQ_ID GLUE(var, __LINE__)

#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(message)

