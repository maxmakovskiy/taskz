#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& source)
{
    std::vector<std::string> result;
    std::string temp;

    for (char c : source)
    {
        if (c == ' ')
        {
            result.push_back(temp);
            temp.clear();
            continue;
        }
        
        temp.push_back(c);
    }
    result.push_back(temp);

    return result;
}

bool contains(const std::vector<std::string> v, const std::string& target)
{
    for (const std::string& el : v)
    {
        if (el == target)
            return true;       
    }

    return false;
}

int main()
{
    std::map<std::string,std::vector<std::string>> buses;

    int n;
    std::cin >> n;

    std::vector<std::string> raw(n);
    std::cin >> std::ws;
    for (std::string& el : raw)
    {
        std::getline(std::cin, el); 
    }

    for (std::string& el : raw)
    {
        std::vector<std::string> temp = split(el);
        
        if (temp[0] == "NEW_BUS")
        {
            std::string bus = temp[1];
            int stopsCount = std::stoi(temp[2]);

            std::vector<std::string> stops(stopsCount);

            int i = 0;
            for (std::string& stop : stops)
            {
                stop = temp[3+i];
                i++;
            }

            buses[bus] = stops;
        }
        else if (temp[0] == "BUSES_FOR_STOP")
        {
            std::string stopName = temp[1];
            std::cout << "STOP " << stopName << ": ";
            for (auto element : buses)
            {
                if (contains(element.second, stopName))
                    std::cout << element.first << " ";
            }
            std::cout << std::endl;
        }
        else if (temp[0] == "STOPS_FOR_BUS")
        {
            std::string busName = temp[1];
            std::cout << "BUS " << busName << ": ";
            for (auto el : buses[busName])
            {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
        else if (temp[0] == "ALL_BUSES")
        {
            for (const auto& el : buses)
            {
                std::cout << el.first << ": ";
                for (std::vector<std::string>::const_iterator it = el.second.begin();
                        it != el.second.end(); it++)
                {
                    if (it == el.second.begin())
                        std::cout << "{" << *it << ", ";
                    else if (it + 1 == el.second.end())
                        std::cout << *it << "}" << std::endl;
                    else
                        std::cout << *it << ", ";
                }
            }
        }

    }


    return 0;
}
