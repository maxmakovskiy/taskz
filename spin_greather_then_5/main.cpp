#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// spinWords("Hey fellow warriors") => "Hey wollef sroirraw" 
// spinWords("This is a test") => "This is a test" 
// spinWords("This is another test") => "This is rehtona test"

std::vector<std::string> split(const std::string &str)
{
    std::vector<std::string> result;
    std::string intermediate;

    for(char c : str)
    {
           if (c == ' ')
        {
            result.push_back(intermediate);
            intermediate.clear();
            continue;
        }
        intermediate.push_back(c);
    }
    result.push_back(intermediate);

    return result;
}

std::string spinWords(const std::string &str)
{
    std::vector<std::string> strings = split(str); 
    std::string result;
   
    for (std::vector<std::string>::iterator it = strings.begin();
            it != strings.end(); it++)
    {
        if (it->length() >= 5 && (it+1) == strings.end())
        {
            std::reverse(it->begin(), it->end());
            result.append(*it);
        }
        else if (it->length() >= 5)
        {
            std::reverse(it->begin(), it->end());
            result.append(*it + " ");
        }
        else if ((it+1) == strings.end())
        {
            result.append(*it);
        }
        else
        {
            result.append(*it + " ");
        }
    }

    return result;
}

int main()
{
    spinWords("Hey fellow warriors");

    return 0;
}

