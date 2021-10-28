#include "responses.h"

std::ostream& operator<<(std::ostream& os, const BusesForStopResponse& r)
{
	if (r.buses.size() == 0) return os;

    os << "Stop " << r.stop << ": ";
    for (const std::string& item : r.buses)
    {
        os << item << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const StopsForBusResponse& r)
{
	if (r.stops.size() == 0) return os;

    os << "Bus " << r.bus << ": ";
    for (const std::string& item : r.stops)
    {
        os << item << " ";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const AllBusesResponse& r)
{
    for (const auto& item : r.buses_to_stop)
    {
        os << "Bus " << item.first << ": ";
        for (const std::string& stop : item.second)
        {
            os << stop << " ";
        }
        os << std::endl;
    }

    return os;
}
