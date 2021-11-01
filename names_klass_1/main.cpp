#include <iostream>
#include <string>
#include <map>

class Person
{
public:
    void ChangeFirstName(int year, const std::string& firstName)
    {
        yearToFirstName[year] = firstName;
    }

    void ChangeLastName(int year, const std::string& lastName)
    {
        yearToLastName[year] = lastName;
    }

    std::string GetFullName(int year)
    {
        std::string firstName = FindName(year, yearToFirstName);
        std::string lastName =  FindName(year, yearToLastName);

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


private:
    std::map<int, std::string> yearToFirstName;
    std::map<int, std::string> yearToLastName;

    std::string FindName(int year, const std::map<int, std::string>& c)
    {
        auto elem = c.find(year);
        if (elem != c.end()) return elem->second;

        if (c.begin()->first > year) return std::string();
        if (c.rbegin()->first < year) return c.rbegin()->second;

        auto it = std::prev(c.upper_bound(year));

        return it->second;
    }
};


int main()
{

    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    for (int year : {1900, 1965, 1990}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        std::cout << person.GetFullName(year) << std::endl;
    }

    return 0;
}
