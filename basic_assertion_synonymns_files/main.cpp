#include <iostream>
#include <string>

#include "synonymns.h"
#include "tests.h"

int main()
{
    AllTests();

    SynonymnsManager manager;

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

            manager.AddNewPair(word1, word2);
        }
        else if (opcode == "COUNT")
        {
            std::string target;
            std::cin >> target;
            
            std::cout << "Number of sinonyms for word '" << target << "' is " << manager.SynonymnCountByWord(target) << std::endl;
        }
        else if (opcode == "CHECK")
        {
            std::string word1;
            std::string word2;
            std::cin >> word1 >> word2;

            if (manager.AreSynonymns(word1, word2))
                std::cout << "YES" << std::endl;
            else
                std::cout << "NO" << std::endl;
        }
    }

    return 0;
}
