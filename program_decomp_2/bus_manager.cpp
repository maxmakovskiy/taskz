#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops)
{
    std::vector<std::string>& stopsByBus = buses_to_stops[bus];

    for (const std::string& stop : stops)
    {
        stopsByBus.push_back(stop);
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const
{
    if (stops_to_buses.find(stop) == stops_to_buses.end())
    {
        std::cout << "No stop" << std::endl;
        return BusesForStopResponse();
    }

    return BusesForStopResponse(stop, stops_to_buses.at(stop));
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const
{
    if (buses_to_stops.find(bus) == buses_to_stops.end())
    {
        std::cout << "No bus" << std::endl;
        return StopsForBusResponse();
    }

    return StopsForBusResponse(bus, buses_to_stops.at(bus));

}

AllBusesResponse BusManager::GetAllBuses() const
{
    if (buses_to_stops.size() == 0)
    {
        std::cout << "No buses" << std::endl;
        return AllBusesResponse();
    }

    return AllBusesResponse(buses_to_stops);
}

