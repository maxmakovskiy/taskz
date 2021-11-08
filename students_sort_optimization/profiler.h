#pragma once

#include <chrono>

class LogDuration
{
public:
    explicit LogDuration(const std::string& msg = "")
        : units("ms")
        , message(msg + ": ")
        , start(std::chrono::steady_clock::now())
    {
    }

    LogDuration(const std::string& units, const std::string& msg)
        : units(units)
        , message(msg + ": ")
        , start(std::chrono::steady_clock::now())
    {
    }

    ~LogDuration()
    {
        auto finish = std::chrono::steady_clock::now();
        auto duration = finish - start;

        std::cerr << message;

        if (units == "s") {
            std::cerr << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " " << units;
        } else if (units == "ms") {
            std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " " << units;
        } else if (units == "us") {
            std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << " " << units;
        } else if (units == "ns") {
            std::cerr << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << " " << units;
        }

        std::cerr << std::endl; 
    }

private:
    std::string units;
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)
#define UNIQ_ID GLUE(var, __LINE__)

#define LOG_DURATION(message) \
    LogDuration UNIQ_ID(message)

#define LOG_DURATION_BY(units, message) \
    LogDuration UNIQ_ID(units, message)

#define LOG_DURATION_SECONDS(message) \
    LogDuration UNIQ_ID("s", message)

#define LOG_DURATION_MILLISECONDS(message) \
    LogDuration UNIQ_ID("ms", message)

#define LOG_DURATION_MICROSECONDS(message) \
    LogDuration UNIQ_ID("us", message)

#define LOG_DURATION_NANOSECONDS(message) \
    LogDuration UNIQ_ID("ns", message)

