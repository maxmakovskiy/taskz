#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// Given a string of words, you need to find the highest scoring word.
// Each letter of a word scores points according to its position in the alphabet: a = 1, b = 2, c = 3 etc.
// You need to return the highest scoring word as a string.

std::vector<std::string> splitString(const std::string& source)
{
    std::vector<std::string> result;
    std::string intermediate;

    for(std::string::size_type i = 0; i < source.size(); i++)
    {
        if (source[i] == '\n' || source[i] == ' ')
        {
            result.push_back(intermediate);
            intermediate.clear();
            continue;
        }
        intermediate.push_back(source[i]);
    }

    result.push_back(intermediate);

    return result;
}

int getScore(const std::string& word)
{
    int result = 0;
    for (std::string::size_type i = 0; i < word.size(); i++)
    {
        int currentCharInt = static_cast<int>(word[i]);
        if (std::isupper(word[i]))
        {
            result += (currentCharInt - 64);
        }
        else
        {
            result += (currentCharInt - 96);
        }

    }

    return result;
}

std::unordered_map<std::string, int> getScoredWords(const std::vector<std::string>& source)
{
    std::unordered_map<std::string, int> result;

    for(std::vector<std::string>::const_iterator it = source.begin();
            it != source.end(); it++)
    {
        result[*it] = getScore(*it);
    }

    return result;
}

std::string highestScoringWord(const std::string &str)
{
    std::vector<std::string> slices = splitString(str);
    std::unordered_map<std::string, int> scoredMap = getScoredWords(slices);
    std::pair<std::string, int> result = *(scoredMap.begin());

    for (std::unordered_map<std::string, int>::iterator it = scoredMap.begin();
           it != scoredMap.end(); it++)
    {
        if (result.second < it->second)
        {
            result = *it;
        }
    }

    return result.first;
}


int main()
{
    std::cout << highestScoringWord("The point of using Lorem Ipsum is that it has a more-or-less normal distribution") << std::endl;

    std::cout << highestScoringWord("what time are we climbing up the volcano") << std::endl;


    return 0;
}
