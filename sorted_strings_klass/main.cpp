#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class SortedStrings
{
public:
    void AddString(const std::string& source)
    {
        strings.push_back(source);
    }

    std::vector<std::string> GetSortedStrings()
    {
        std::sort(std::begin(strings), std::end(strings), 
                [] (const std::string& s1, const std::string& s2)
                {
                    char c1 = tolower(s1[0]);
                    char c2 = tolower(s2[0]);

                    return c1 < c2 ? true : false;
                });

        return strings;
    }

private:
    std::vector<std::string> strings;
};

void PrintSortedStrings(SortedStrings& obj)
{
    for (const std::string& s : obj.GetSortedStrings())
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main()
{
    SortedStrings strs;

    strs.AddString("second");
    strs.AddString("first");
    PrintSortedStrings(strs);

    strs.AddString("second");
    PrintSortedStrings(strs);

    strs.AddString("third");
    strs.AddString("second");
    PrintSortedStrings(strs);

    return 0;
}
