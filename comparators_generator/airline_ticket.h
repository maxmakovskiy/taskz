#pragma once

#include <string>
#include <tuple> 

using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

bool operator!=(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) !=
        tie(rhs.year, rhs.month, rhs.day);
}
bool operator<(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) < 
        tie(rhs.year, rhs.month, rhs.day);
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << std::to_string(date.year) + "/" << std::to_string(date.month) + "/" + std::to_string(date.day);

	return os;
}

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};
