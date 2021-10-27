#include <iostream>
#include <map>
#include <set>
#include <string>
#include <exception>
#include <sstream>

using Synonymns = std::map<std::string, std::set<std::string>>;

class SynonymnsManager
{
public:
    void AddNewPair(const std::string& word1, const std::string& word2)
    {
        synonymns[word1].insert(word2);
//        synonymns[word2].insert(word1);

        // example for checking unit-testing
        synonymns[word2].insert(word2);

    }
    
    size_t SynonymnCountByWord(const std::string& word) const
    {
        if (synonymns.find(word) == synonymns.end()) return 0u;

        return synonymns.at(word).size();
    }
    
    bool AreSynonymns(const std::string& word1, const std::string& word2) const
    {
        std::set<std::string> current = synonymns.at(word1);
        if (current.find(word2) != current.end())
            return true;
        else
            return false;
    }

    Synonymns GetAll() const
    {
        return synonymns;
    }

private:
    Synonymns synonymns;

};

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value> m)
{
    if (m.size() == 0) return os;

    os << "{";
    int i = 0;
    for (const auto& el : m)
    {
        if (i+1 == m.size())
        {
            os <<  "(" << el.first << ": " << el.second << ")}";
            break;
        }

        os <<  "(" << el.first << ": " << el.second << "), ";
        i++;
    }
    
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> s)
{
    if (s.size() == 0) return os;
   
    os << "[";

    size_t i = 0;
    for (const T& el : s)
    {
        if (i+1 == s.size())
        {
            os << el << "]";
            break;
        }

        os << el << ", ";

        i++;
    }
    
    return os;
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " HINT: " << hint;
        throw std::runtime_error(os.str()); 
    }
}

void Assert(bool b, const std::string& hint)
{
    AssertEqual(b, true, hint);
}

template <typename TestFunc>
void RunTest(TestFunc func, const std::string& testName)
{
    try
    {
        func();
    }
    catch (std::runtime_error& e)
    {
        std::cout << testName << " fail: " << e.what() << std::endl;
    }
}

void TestAddNewPair()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
        
    const Synonymns expected = { 
        {"word1", {"word2", "word3"}},
        {"word2", {"word1", "word3", "word4"}},
        {"word3", {"word1", "word2"}},
        {"word4", {"word2"}}
    };
        
    AssertEqual(manager.GetAll(), expected, "Add new pairs to empty dictionary");
    
    std::cout << "AddNewPair OK" << std::endl;
}

void TestSynonymnCountByWord()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
   
    AssertEqual(manager.SynonymnCountByWord("word1"), 2u, "SynonymnCountByWord(word1)");
    AssertEqual(manager.SynonymnCountByWord("word2"), 3u, "SynonymnCountByWord(word2)");
    AssertEqual(manager.SynonymnCountByWord("word3"), 2u, "SynonymnCountByWord(word3)");
    AssertEqual(manager.SynonymnCountByWord("word4"), 1u, "SynonymnCountByWord(word4)");
    AssertEqual(manager.SynonymnCountByWord("word5"), 0u, "SynonymnCountByWord(word5)");

    std::cout << "SynonymnsCountByWord OK" << std::endl;
}

void TestAreSynonymns()
{
    SynonymnsManager manager;
    manager.AddNewPair("word1", "word2");
    manager.AddNewPair("word1", "word3");
    manager.AddNewPair("word2", "word3");
    manager.AddNewPair("word2", "word4");
   
    Assert(manager.AreSynonymns("word1", "word2"), "word1 is synonymn for word2");
    Assert(manager.AreSynonymns("word2", "word3"), "word2 is synonymn for word3");
    Assert(manager.AreSynonymns("word2", "word4"), "word2 is synonymn for word4");
    Assert(!manager.AreSynonymns("word3", "word4"), "word2 is not synonymn for word4");


    std::cout << "TestAreSynonymns OK" << std::endl;
}

int main()
{
    RunTest(TestAddNewPair, "TestAddNewPair");
    RunTest(TestSynonymnCountByWord, "TestSynonymnCountByWord");
    RunTest(TestAreSynonymns, "TestAreSynonymns");

/*
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
*/

    return 0;
}
