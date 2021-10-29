#include <iostream>
#include <vector>
#include <algorithm>

enum class Gender
{
    FEMALE,
    MALE
};

struct Person
{
    int age;
    Gender gender;
    bool isEmployed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt rangeBegin, InputIt rangeEnd)
{
    if (rangeBegin == rangeEnd) return 0;

    std::vector<typename InputIt::value_type> rangeCopy(rangeBegin, rangeEnd);
    auto middle = rangeCopy.begin() + rangeCopy.size() / 2;

    std::nth_element(
            rangeCopy.begin(), middle, rangeCopy.end(),
            [] (const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            });
    
    return middle->age;
}

void PrintStats(std::vector<Person> persons)
{
    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;

    auto firstMalePos = std::partition(persons.begin(), persons.end(),
            [] (Person& p) {
                return p.gender == Gender::FEMALE;
            });

    std::vector<Person> females(persons.begin(), firstMalePos);
    std::vector<Person> males(firstMalePos, persons.end());

    std::cout << "Median age for females = " << ComputeMedianAge(females.begin(), females.end()) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(males.begin(), males.end()) << std::endl;

    auto firstUnemployedFemale = std::partition(females.begin(), females.end(),
            [] (Person& p) {
                return p.isEmployed;
            });
    auto firstUnemployedMale = std::partition(males.begin(), males.end(),
            [] (Person& p) {
                return p.isEmployed;
            });

    std::cout << "Median age for employed females = " << ComputeMedianAge(females.begin(), firstUnemployedFemale) << std::endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(firstUnemployedFemale, females.end()) << std::endl;

    std::cout << "Median age for employed males = " << ComputeMedianAge(males.begin(), firstUnemployedMale) << std::endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(firstUnemployedMale, males.end()) << std::endl;

}

int main()
{
    std::vector<Person> persons = {
        {31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true}
    };

    PrintStats(persons);

    return 0;
}
