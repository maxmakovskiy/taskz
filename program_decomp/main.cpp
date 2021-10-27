#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

std::istream& operator>>(std::istream& is, Query& q)
{
    std::string opType;
    is >> opType;
    if (opType == "NEW_BUS")
    {
        q.type = QueryType::NewBus;

        is >> q.bus;

        int stopsCount;
        is >> stopsCount;
        q.stops.clear();
        for (int i = 0; i < stopsCount; i++)
        {
            std::string temp;
            is >> temp;
            q.stops.push_back(temp);
        }
    }
    else if (opType == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;

        is >> q.stop;
    }
    else if (opType == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;

        is >> q.bus;
    }
    else if (opType == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}

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

class BusManager {
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops)
    {
        std::vector<std::string>& stopsByBus = buses_to_stops[bus];

        for (const std::string& stop : stops)
        {
            stopsByBus.push_back(stop);
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const std::string& stop) const
    {
        if (stops_to_buses.find(stop) == stops_to_buses.end())
        {
            std::cout << "No stop" << std::endl;
            return BusesForStopResponse();
        }

        return BusesForStopResponse(stop, stops_to_buses.at(stop));
    }

    StopsForBusResponse GetStopsForBus(const std::string& bus) const
    {
        if (buses_to_stops.find(bus) == buses_to_stops.end())
        {
            std::cout << "No bus" << std::endl;
            return StopsForBusResponse();
        }

        return StopsForBusResponse(bus, buses_to_stops.at(bus));

    }

    AllBusesResponse GetAllBuses() const
    {
        if (buses_to_stops.size() == 0)
        {
            std::cout << "No buses" << std::endl;
            return AllBusesResponse();
        }

        return AllBusesResponse(buses_to_stops);
    }

private:
    std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;
};


int main() {
  int query_count;
  Query q;

  std::cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
	  std::cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
    	std::cout << bm.GetBusesForStop(q.stop) << std::endl;
      break;
    case QueryType::StopsForBus:
    	std::cout << bm.GetStopsForBus(q.bus) << std::endl;
      break;
    case QueryType::AllBuses:
    	std::cout << bm.GetAllBuses() << std::endl;
      break;
    }
  }

  return 0;
}
