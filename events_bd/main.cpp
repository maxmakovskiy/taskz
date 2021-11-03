#include <iostream>
#include <string>
#include <sstream>
#include "db.h"
#include "date.h"
#include "query.h"

int main() 
{
    Database db;
    
    std::string command;
    std::cout << "=> ";
    while (std::getline(std::cin, command)) 
    {
        Query query;
        std::stringstream ss(command);

        ss >> query;
        
        if (query.type == OperationType::EMPTY)
        {
            std::cout << "=> ";
            continue;
        }
        if (query.type == OperationType::ADD)
        {
            if (query.targetDate == Date())
            {
                std::cout << "=> ";
                continue;
            }

            db.AddEvent(query.targetDate, query.eventSource);
        }
        else if (query.type == OperationType::DELETE_EVENT)
        {
            bool result = db.DeleteEvent(query.targetDate, query.eventSource);
            std::cout << (result ? ">>Deleted successfully" : ">>Event not found") << std::endl;
        }
        else if (query.type == OperationType::DELETE_DATE)
        {
            int result = db.DeleteDate(query.targetDate);
            std::cout << ">>Deleted: " << result << " events" << std::endl;
        }
        else if (query.type == OperationType::FIND)
        {
            auto result = db.Find(query.targetDate);
            if (result.size() == 0)
            {
                std::cout << query.targetDate.ToString() << ": events no found" << std::endl;
                std::cout << "=> ";

                continue;
            }

            std::cout << query.targetDate.ToString() << ":" << std::endl;
            for (auto it = result.begin(); it != result.end(); it++)
            {
                std::cout << "\t-" << *it << std::endl;
            }
        }
        else if (query.type == OperationType::PRINT)
        {
            db.Print();
        }
        else
        {
            std::cout << "Unknown command: " << query.typeName << std::endl;
        }

        std::cout << "=> ";
    }

    return 0;
}
