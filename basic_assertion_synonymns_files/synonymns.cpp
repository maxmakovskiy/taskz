#include "synonymns.h"

void SynonymnsManager::AddNewPair(const std::string& word1, const std::string& word2)
{
    synonymns[word1].insert(word2);
    synonymns[word2].insert(word1);

    // example for checking unit-testing
    //synonymns[word2].insert(word2);

}
    
size_t SynonymnsManager::SynonymnCountByWord(const std::string& word) const
{
    if (synonymns.find(word) == synonymns.end()) return 0u;

    return synonymns.at(word).size();
}
    
bool SynonymnsManager::AreSynonymns(const std::string& word1, const std::string& word2) const
{
    std::set<std::string> current = synonymns.at(word1);
    if (current.find(word2) != current.end())
        return true;
    else
        return false;
}

Synonymns SynonymnsManager::GetAll() const
{
    return synonymns;
}

