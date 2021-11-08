#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <set>

#include "test.h"
#include "profiler.h"

class Learner {
public:
    int Learn(const std::vector<std::string>& words) 
    {
        int newWords = 0;
        for (const auto& word : words) 
        {
            if (dict.find(word) == dict.end()) {
                ++newWords;
                dict.insert(word);
            }
        }
        return newWords;
    }

    std::vector<std::string> KnownWords() 
    {
        return std::vector<std::string>(dict.begin(), dict.end());
    }

private:
    std::set<std::string> dict;
};

void TestLearn()
{
    Learner learner;
   
    std::vector<std::string> words;
    for (int i = 0; i < 100; i++) {
        words.push_back("word" + std::to_string(i));
    }
   
    int wordsCount = 0;
    {
        LOG_DURATION("Learn");
        wordsCount = learner.Learn(words);
    }

    ASSERT_EQUAL(wordsCount, words.size());
}

void TestKnownWords()
{
    Learner learner;
    
    std::vector<std::string> expected;
    for (int i = 0; i < 100; i++) {
        expected.push_back("word" + std::to_string(i));
    }
    std::sort(expected.begin(), expected.end());

    std::vector<std::string> mockInputData;
    for (int i = 0; i < 100; i++) {
        mockInputData.insert(mockInputData.end(), expected.begin(), expected.end());
    } 
    
    learner.Learn(mockInputData);

    std::vector<std::string> result;
    {
        LOG_DURATION("KnownWords");
        result = learner.KnownWords();
    }

    ASSERT_EQUAL(expected, result);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestLearn);
    RUN_TEST(tr, TestKnownWords);

    return 0;
}
