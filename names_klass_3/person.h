#pragma once

#include <string>
#include <map>
#include <iterator>

class Person
{
public:
    Person(std::string firstName, std::string lastName, int year);

    void ChangeFirstName(int year, const std::string& firstName);

    void ChangeLastName(int year, const std::string& lastName);

    std::string GetFullName(int year);

    std::string GetFullNameWithHistory(int year);

private:
    std::string _firstName;
    std::string _lastName;
    int _year;

    std::map<int, std::string> yearToFirstName;
    std::map<int, std::string> yearToLastName;

    std::map<int, std::string>::const_iterator FindName(int year, const std::map<int, std::string>& c);

    std::string GetHistory(std::map<int, std::string>::const_iterator it, const std::map<int, std::string>& c);

};
