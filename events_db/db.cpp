#include "date.h"
#include "db.h"

void Database::AddEvent(const Date& date, const std::string& event)
{
    container[date].push_back(event);
}

bool Database::DeleteEvent(const Date& date, const std::string& event)
{
    std::vector<std::string> eventToDay = container[date];
    auto current = std::find(eventToDay.begin(), eventToDay.end(), event);

    if (eventToDay.empty() || current == eventToDay.end())
    {
        return false;
    }
    
    container[date].erase(current);

    return true;
}

int Database::DeleteDate(const Date& date)
{
    if (container.count(date) == 0) return 0;

    int counter = container[date].size();
    container[date].clear();
    return counter;
}

std::vector<std::string> Database::Find(const Date& date) const
{
    return container.at(date);
}
  
void Database::Print() const
{
    for (auto it = container.begin(); it != container.end(); it++)
    {
        if (it->second.size() == 0) continue;

        std::cout << it->first.ToString() << ":" << std::endl;
        
        int k = 0;
        for (const std::string& i : it->second)
        {
            if (k == it->second.size()-1)
            {
                std::cout << "\t-" << i;
                break;
            }
            
            std::cout << "\t-" << i << std::endl; 
            k++;
        }
        std::cout << std::endl;
    }

}

