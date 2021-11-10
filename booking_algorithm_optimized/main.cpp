#include <cstdint>
#include <string>
#include <deque>
#include <map>

#include "test.h"
#include "profiler.h"

struct Query
{
    int64_t time;
    std::string hotel_name;
    uint32_t client_id;
    size_t room_count;
};

class BookingManager
{
public:
    void Booking(const Query& q) 
    {
        Adjust(q.time);
        
        base.push_back(q);
        hotelToClient[q.hotel_name]++;
        hotelToRooms[q.hotel_name] += q.room_count;
    }

    int ClientsNumberIn(const std::string& hotelName)
    {
        return hotelToClient[hotelName];
    }

    int BookedRoomsIn(const std::string& hotelName)
    {
        return hotelToRooms[hotelName];
    }

private:
    std::deque<Query> base;
    const int64_t SECONDS_IN_DAY = 86400;
    std::map<std::string, int> hotelToRooms;
    std::map<std::string, int> hotelToClient;

    void Adjust(const int64_t& time)
    {
        while (!base.empty() &&
                 (base.front().time <= time-SECONDS_IN_DAY))
        {
            auto temp = base.front();
            hotelToClient[temp.hotel_name]--;
            hotelToRooms[temp.hotel_name] -= temp.room_count;
            base.pop_front();
        }

    }
};

void TestEmpty()
{
    BookingManager manager;
    
    ASSERT_EQUAL(manager.ClientsNumberIn("Marriott"), 0);
    ASSERT_EQUAL(manager.BookedRoomsIn("FourSeasons"), 0);
}

void TestCorrectness1()
{
    BookingManager manager;

    manager.Booking({10, "FourSeasons", 1, 2});
    manager.Booking({10, "Marriott", 1, 1});
    manager.Booking({86409, "FourSeasons", 2, 1});
    
    ASSERT_EQUAL(manager.ClientsNumberIn("FourSeasons"), 2);
    ASSERT_EQUAL(manager.BookedRoomsIn("FourSeasons"), 3);
    ASSERT_EQUAL(manager.ClientsNumberIn("Marriott"), 1);
}

void TestCorrectness2()
{
    BookingManager manager;

    manager.Booking({10, "FourSeasons", 1, 2});
    manager.Booking({10, "Marriott", 1, 1});
    manager.Booking({86409, "FourSeasons", 2, 1});
    manager.Booking({86410, "Marriott", 2, 10});
    
    ASSERT_EQUAL(manager.BookedRoomsIn("FourSeasons"), 1);
    ASSERT_EQUAL(manager.BookedRoomsIn("Marriott"), 10);
}

void TestBench()
{
    const uint32_t COUNT = 1000000;
    BookingManager manager;
    
    {
        LOG_DURATION_MILLISECONDS("Booking over " + std::to_string(COUNT));
        for (uint32_t i = 0; i < COUNT; i++)
        {
            manager.Booking({i+1, "hotel" + std::to_string(i), i+3, i+5});
        }
    }
    
    {
        LOG_DURATION_MILLISECONDS("ClientsNumberIn over " + std::to_string(COUNT));
        for (uint32_t i = 0; i < COUNT; i++)
        {
            manager.ClientsNumberIn("hotel" + std::to_string(i));
        }
 
    }

    {
        LOG_DURATION_MILLISECONDS("ClientsNumberIn over " + std::to_string(COUNT));
        for (uint32_t i = 0; i < COUNT; i++)
        {
            manager.BookedRoomsIn("hotel" + std::to_string(i));
        }
 
    }


}

int main()
{
    TestRunner runner;

    RUN_TEST(runner, TestEmpty);
    RUN_TEST(runner, TestCorrectness1);
    RUN_TEST(runner, TestCorrectness2);
    RUN_TEST(runner, TestBench);


    return 0;
}
