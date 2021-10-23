#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>

int nearNum(int target, const std::vector<int> source)
{
    int left, right;

    for (int i = 0; i < source.size(); i++)
    {
        left = source[i];
        right = source[i + 1];

        if (target >= left && target < right)
            return left;
    }
    
    return 0;
}

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

    std::string GetFullNameByYear(int year)
    {
        int keyForFirst = chooseKey(year, yearToFirstName);
        std::string firstName = keyForFirst != 0 ? yearToFirstName[keyForFirst] : "unknow first name";
        int keyForSecond = chooseKey(year, yearToLastName);
        std::string secondName = keyForSecond != 0 ? yearToLastName[keyForSecond] : "unknow second name";

        return firstName + " " + secondName;        
    }

private:
    std::map<int, std::string> yearToFirstName;
    std::map<int, std::string> yearToLastName;

    int chooseKey(int year, const std::map<int, std::string>& collection)
    {
        std::vector<int> keys = keysFromMap(collection);
        
        if (year >= keys.back())
            return keys.back(); 
        else if (year >= keys.front() && year < keys.back())
            return nearNum(year, keys);
        
        // nothing to find
        return 0;
    };

    std::vector<int> keysFromMap(const std::map<int, std::string>& source)
    {
        std::vector<int> result;
        for (const auto& el : source)
            result.push_back(el.first);

        return result;
    }
};


int main()
{
    Person person;
    person.ChangeLastName(1967, "Segeeva");
    person.ChangeFirstName(1966, "Polina");
    std::cout << person.GetFullNameByYear(1932) << std::endl;
    std::cout << person.GetFullNameByYear(1966) << std::endl;
    std::cout << person.GetFullNameByYear(1967) << std::endl;


    return 0;
}
