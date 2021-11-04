#pragma once
#include <sstream>
#include <string>
#include <tuple>

class Date {
friend bool operator<(const Date& lhs, const Date& rhs);
friend bool operator==(const Date& lhs, const Date& rhs);
public:
    Date();
    Date(int year, int month, int day);

    std::string ToString() const;

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);

private:
    int year;
    int month;
    int day;
};

