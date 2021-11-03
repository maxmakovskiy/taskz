#pragma once
#include <regex>
#include <iostream>
#include "date.h"

enum class OperationType
{
    ADD, DELETE_EVENT, DELETE_DATE, FIND, PRINT, EMPTY, UNKNOWN
};

struct Query
{
    OperationType type;
    std::string typeName;
    Date targetDate;
    std::string eventSource;
};

bool ValidateDate(const std::string& raw, Date& date);

void operator>>(std::stringstream& is, Query& query);

