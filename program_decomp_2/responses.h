#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

struct BusesForStopResponse {
    std::string stop;
    std::vector<std::string> buses;

    BusesForStopResponse(std::string stop, std::vector<std::string> buses)
    {
        this->stop = stop;
        this->buses = buses;
    }

    BusesForStopResponse()
    {
    }
};

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    std::string bus;
    std::vector<std::string> stops;

    StopsForBusResponse(std::string bus, std::vector<std::string> stops)
    {
        this->bus = bus;
        this->stops = stops;
    }

    StopsForBusResponse()
    {
    }
};

std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> buses_to_stop;

    AllBusesResponse(std::map<std::string, std::vector<std::string>> buses_to_stop)
    {
        this->buses_to_stop = buses_to_stop;
    }

    AllBusesResponse()
    {
    }
};

std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r);
