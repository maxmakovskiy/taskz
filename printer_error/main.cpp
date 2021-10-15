#include <iostream>
#include <string>
#include <unordered_map>

/*
    s="aaabbbbhaijjjm"
    printer_error(s) => "0/14"
    s="aaaxbbbbyyhwawiwjjjwwm"
    printer_error(s) => "8/22"
*/

std::string print_error(const std::string& source)
{
    std::string result;
    int length = source.size();
    int errorCount = 0;
    std::unordered_map<char, int> tmp;
    
    for (int i = 0; i < length; i++)
    {
        tmp[source[i]] = 0; 
    }

    for (int i = 0; i < length; i++)
    {
        tmp[source[i]]++; 
    }

    for (auto& it : tmp)
    {
        if (it.first > 109 && it.first < 123)
        {
            errorCount += it.second;
        }
    }

    result = std::to_string(errorCount) + "/" + std::to_string(length);
    return result;

}

int main()
{
    std::cout << print_error("aaabbbbhaijjjm") << std::endl;  
    std::cout << print_error("aaaxbbbbyyhwawiwjjjwwm") << std::endl;  


    return 0;
}

