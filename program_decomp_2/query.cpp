#include "query.h"

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
