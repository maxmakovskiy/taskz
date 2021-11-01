#include "person.h"

Person::Person(std::string firstName, std::string lastName, int year)
{
    this->_firstName = firstName;
    this->_lastName = lastName;
    this->_year = year;

    yearToFirstName[year] = firstName;
    yearToLastName[year] = lastName;
}

std::map<int, std::string>::const_iterator Person::FindName(int year, const std::map<int, std::string>& c)
{
	auto elem = c.find(year);
    if (elem != c.end()) return elem;

    if (c.begin()->first > year) return c.end();

    if (c.rbegin()->first < year)
    {
    	return std::next(c.begin(), c.size()-1);
    }

    return std::prev(c.upper_bound(year));
}

std::string Person::GetHistory(std::map<int, std::string>::const_iterator it, const std::map<int, std::string>& c)
{
	std::string result;

    auto first = c.begin();
	if (first == it)
	{
		return result;
	}

    bool isFirst = true;
    result += " (";
    for (; first != it; first++)
    {
    	if (isFirst)
    	{
    		result += first->second;
    		isFirst = false;
    		continue;
    	}
    	result += ", " + first->second;
    }

    result += ") ";

    return result;
}

void Person::ChangeFirstName(int year, const std::string& firstName)
{
    if (this->_year < year) {
	    yearToFirstName[year] = firstName;
    }
}

void Person::ChangeLastName(int year, const std::string& lastName)
{
    if (this->_year < year) {
    	yearToLastName[year] = lastName;
    }
}

std::string Person::GetFullName(int year)
{
    if (this->_year > year) return "No person";

	std::string firstName = FindName(year, yearToFirstName)->second;
    std::string lastName =  FindName(year, yearToLastName)->second;

    if (firstName.empty() && lastName.empty())
    {
        return "Incognito";
    }

    if (firstName.empty())
    {
        return lastName + " with unknown first name";
    }
    else if (lastName.empty())
    {
        return firstName + " with unknown last name";
    }

    return firstName + " " + lastName;
}

std::string Person::GetFullNameWithHistory(int year)
{
    if (this->_year > year) return "No person";

	std::map<int, std::string>::const_iterator firstIt, lastIt;
    firstIt = FindName(year, yearToFirstName);
    std::string firstName = (firstIt != yearToFirstName.end()) ? firstIt->second : std::string();
    lastIt = FindName(year, yearToLastName);
    std::string lastName = (lastIt != yearToLastName.end()) ? lastIt->second : std::string();

    if (firstName.empty() && lastName.empty())
    {
    	return "Incognito";
    }

    if (firstName.empty())
    {
        std::string history = GetHistory(lastIt, yearToLastName);
        if (history.empty()) history += " ";

		return lastName + history + "with unknown first name";
    }
    else if (lastName.empty())
    {
        // history only for firstName
        std::string history = GetHistory(firstIt, yearToFirstName);
        if (history.empty()) history += " ";

        return firstName + history + "with unknown last name";
    }

    // full history
    std::string historyFirst = GetHistory(firstIt, yearToFirstName);
    std::string historyLast = GetHistory(lastIt, yearToLastName);

    if (historyFirst.empty()) historyFirst += " ";
    if (historyLast.empty()) historyLast += " ";

    return firstName + historyFirst + lastName + historyLast;
}
