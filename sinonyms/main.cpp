#include <iostream>
#include <map>
#include <set>


int main()
{
    std::map<std::string, std::set<std::string>> sinonymsDict;

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::string opcode;
        std::cin >> opcode;

        if (opcode == "ADD")
        {
            std::string word1;
            std::string word2;
            std::cin >> word1 >> word2;

            sinonymsDict[word1].insert(word2);
            sinonymsDict[word2].insert(word1);
        }
        else if (opcode == "COUNT")
        {
            std::string target;
            std::cin >> target;
            
            std::cout << "Number of sinonyms for word " << target << " is " << sinonymsDict[target].size() << std::endl;
        }
        else if (opcode == "CHECK")
        {
            std::string word1;
            std::string word2;
            std::cin >> word1 >> word2;

            if (sinonymsDict[word1].count(word2))
                std::cout << "YES" << std::endl;
            else
                std::cout << "NO" << std::endl;
        }

    }

    return 0;
}
