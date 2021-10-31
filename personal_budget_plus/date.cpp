#include "date.h"

int Date::DaysInCurrentYear() const
{
    int result = 0;
    bool leap = false;

    if (this->year % 4 == 0)
    {
        leap = true;
    }

    for (int i = 1; i <= this->month; i++)
    {
        switch(i) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            result += 31;
            break;
        case 2:
            if (leap) {
                result += 29;
            } else {
                result += 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            result += 30;
            break;
        }
    }

    result += this->day;

    return result;
}

const Date& Date::operator++()
{
    if (this->month == 12 && this->day == 31)
    {
        this->year++;
        this->month = 1;
        this->day = 1;
        return *this;
    }

    switch(this->month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (this->day == 31) {
            this->month++;
            this->day = 1;
        }
        else {
            this->day++;
        }
        break;
    case 2:
        if (this->year % 4 == 0) {
            if (this->day == 29) {
                this->month++;
                this->day = 1;
            } else {
                this->day++;
            }
        } else {
            if (this->day == 28) {
                this->month++;
                this->day = 1;
            } else {
                this->day++;
            }
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (this->day == 30) {
            this->month++;
            this->day = 1;
        } else {
            this->day++;
        }
        break;
    }

    return *this;
}

std::vector<Date> operator-(const Date& lhs, const Date& rhs)
{
    std::vector<Date> result;

    if (lhs == rhs) return result;

    auto less = lhs < rhs ? lhs : rhs;
    auto greather = lhs < rhs ? rhs : lhs;

    while(less != greather)
    {
        result.push_back(less);
        ++less;
    }

    result.push_back(less);

    return result;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    if (lhs.year != rhs.year) return false;

    if (lhs.month != rhs.month) return false;

    if (lhs.day != rhs.day) return false;

    return true;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
    if (lhs.year != rhs.year) return true;

    if (lhs.month != rhs.month) return true;

    if (lhs.day != rhs.day) return true;

    return false;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.year != rhs.year)
    {
        return lhs.year < rhs.year;
    }
    else if (lhs.month != rhs.month)
    {
        return lhs.month < rhs.month;
    }
    else
    {
        return lhs.day < rhs.day;
    }
}


std::istream& operator>>(std::istream& is, Date& date)
{
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.year << "/" << date.month << "/" << date.day;
    return os;
}

int DaysDiff(const Date& lhs, const Date& rhs)
{
    std::vector<Date> result = lhs - rhs;
    return result.size();
}

bool operator>(const Date& lhs, const Date& rhs)
{
	if (lhs.year != rhs.year)
    {
        return lhs.year > rhs.year;
    }
    else if (lhs.month != rhs.month)
    {
        return lhs.month > rhs.month;
    }
    else
    {
        return lhs.day > rhs.day;
    }

}
