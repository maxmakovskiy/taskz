#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "date.h"

class Database {
public:
    void AddEvent(const Date& date, const std::string& event);
    bool DeleteEvent(const Date& date, const std::string& event);
    int  DeleteDate(const Date& date);

    std::vector<std::string> Find(const Date& date) const;
    void Print() const;

private:
    std::map<Date, std::vector<std::string>> container;
};

