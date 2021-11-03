#include "date.h"

Date::Date()
{
    year = 1;
    month = 1;
    day = 1;
}

Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

int Date::GetYear() const
{
    return year;
}

int Date::GetMonth() const
{
    return month;
}

int Date::GetDay() const
{
    return day;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.year != rhs.year) return lhs.year < rhs.year;
    if (lhs.month != rhs.month) return lhs.month < rhs.month;
    return lhs.day < rhs.day;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) 
        == std::tie(rhs.year, rhs.month, rhs.day);    
}

void Date::SetYear(int year)
{
    this->year = year;
}

void Date::SetMonth(int month)
{
    this->month = month;
}

void Date::SetDay(int day)
{
    this->day = day;
}

std::string Date::ToString() const
{
    return (std::to_string(this->year) + "-" + std::to_string(this->month) + "-" + std::to_string(this->day));
}


