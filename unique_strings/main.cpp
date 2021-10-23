#include <iostream>
#include <set>
#include <string>

int main()
{
    int n;
    std::cin >> n;
    std::set<std::string> strs;

    for (int i = 0; i < n; i++)
    {
        std::string temp;
        std::cin >> temp;
        strs.insert(temp);
    }

    std::cout << "Number of unique input's strings: " << strs.size() << std::endl;


    return 0;
}
