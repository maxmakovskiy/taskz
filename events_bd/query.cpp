#include "query.h"

bool ValidateDate(const std::string& raw, Date& date)
{
    if (raw.size() != 10) return false;
    
    std::string day;

    std::regex exp("[0-9]{4}.[0-9]{1,2}.[0-9]{1,2}");
    if (!std::regex_search(raw, exp)) return false;

    date.SetYear(std::stoi(raw.substr(0, 4)));
    date.SetMonth(std::stoi(raw.substr(5, 7)));
    date.SetDay(std::stoi(raw.substr(8, 10)));

    return true;
}

void operator>>(std::stringstream& is, Query& query)
{
    std::string op;
    is >> op;

    if (op.empty())
    {
        query.type = OperationType::EMPTY;
    }
    else if (op == "Add")
    {
        query.type = OperationType::ADD;
        query.typeName = op;

        std::string date;
        is >> date;

        Date target;
        if(ValidateDate(date, target))
        {
            query.targetDate = target;
        }
        else 
        {
            std::cout << "Date value is invalid: " << date << std::endl;
            return;
        }
     
        // making bicycle
        std::string buffer;
        while(!is.eof())
        {
            std::string temp;
            is >> temp;
            temp += " ";
            buffer.append(temp);
        }
        buffer.pop_back();

        query.eventSource = buffer;        
    }
    else if (op == "Del")
    {
        std::string date;
        is >> date;

        // TODO: make like ADD case
        Date target;
        query.targetDate = ValidateDate(date, target) ? target : Date();

        query.typeName = op;
        if (!is.eof())
        {
            is >> query.eventSource;        
            query.type = OperationType::DELETE_EVENT;
        }
        else
        {
            query.type = OperationType::DELETE_DATE; 
        }
    }
    else if (op == "Find")
    {
        query.type = OperationType::FIND;
        query.typeName = op;
        
        std::string date;
        is >> date;

        Date target;
        query.targetDate = ValidateDate(date, target) ? target : Date();

    }
    else if (op == "Print")
    {
        query.type = OperationType::PRINT;
        query.typeName = op;
    }
    else
    {
        query.type = OperationType::UNKNOWN;
        query.typeName = op;
    }
         
    return;
}
