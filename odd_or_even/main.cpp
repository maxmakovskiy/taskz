#include <iostream>
#include <string>
#include <vector>

/*
    Input: [0]
    Output: "even"

    Input: [0, 1, 4]
    Output: "odd"

    Input: [0, -1, -5]
    Output: "even"
*/

std::string odd_or_even(const std::vector<int> &arr)
{
    if (arr.empty()) return "even";
    if (*(arr.begin()) == 0 && (arr.size() == 1)) return "even";

    int temp = 0;
    for (auto it = arr.begin(); it != arr.end(); it++)
    {
       temp += *(it); 
    }

    if (temp % 2 == 0)
        return "even";

    return "odd"; 
}

int main()
{
    std::cout << "odd_or_event(): " << odd_or_even(std::vector<int>()) << std::endl; 
    std::cout << "odd_or_event([0]): " << odd_or_even(std::vector<int>{0}) << std::endl; 
    std::cout << "odd_or_event([0, 1, 4]): " << odd_or_even(std::vector<int>{0,1,4}) << std::endl; 
    std::cout << "odd_or_event([0, -1, -5]): " << odd_or_even(std::vector<int>{0,-1,-5}) << std::endl; 

    return 0;
}

