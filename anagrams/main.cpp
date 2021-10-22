#include <iostream>
#include <map>
#include <vector>

std::map<char, int> letter_counts(const std::string& source)
{
    std::map<char, int> result;

    for (char c : source)
    {
        result[c]++;
    }

    return result;
}


bool is_anagrams(const std::string& word1, const std::string& word2)
{
    if (letter_counts(word1) == letter_counts(word2))
        return true;

    return false;
}

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::string> raw(n);

    std::cin >> std::ws;

    for (std::string& el : raw)
    {
        std::getline(std::cin, el);
    }

    for (int i = 0; i < raw.size(); i++)
    {
        std::string::size_type pos = raw[i].find(" ");
        std::string word1 = raw[i].substr(0, pos);
        std::string word2 = raw[i].substr(pos+1);
        std::cout << "is_anagrams(" << word1 << ", " << word2 << ") => " << is_anagrams(word1, word2) << std::endl;
    }

    return 0;
}
