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

std::istream& operator>>(std::istream& is, Date& date)
{
	std::string year;
	std::string month;
	std::string day;
	std::getline(is, year, '-');
	std::getline(is, month, '-');
	std::getline(is, day, '\n');

	date.year = std::stoi(year);
	date.month = std::stoi(month);
	date.day = std::stoi(day);

	return is;
}

std::istream& operator>>(std::istream& is, Time& time)
{
	std::string hours;
	std::string minutes;
	std::getline(is, hours, ':');
	std::getline(is, minutes, '\n');

	time.hours = std::stoi(hours);
	time.minutes = std::stoi(minutes);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
	os << std::to_string(time.hours) + ":" << std::to_string(time.minutes);
    return os;
}

bool operator!=(const Time& lhs, const Time& rhs)
{
    return tie(lhs.hours, lhs.minutes) !=
        tie(rhs.hours, rhs.minutes);
}

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
