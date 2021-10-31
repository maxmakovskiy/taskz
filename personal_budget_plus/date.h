#pragma once

#include <vector>
#include <iostream>

struct Date
{ // YYYY-MM-DD
    int year;
    int month;
    int day;

    Date()
    {
        year = 0;
        month = 0;
        day = 0;
    }

    Date(int year, int month, int day)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }

    int DaysInCurrentYear() const;

    const Date& operator++();
};

std::vector<Date> operator-(const Date& lhs, const Date& rhs);

bool operator<(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);

std::istream& operator>>(std::istream& is, Date& date);

std::ostream& operator<<(std::ostream& os, const Date& date);

int DaysDiff(const Date& lhs, const Date& rhs);
