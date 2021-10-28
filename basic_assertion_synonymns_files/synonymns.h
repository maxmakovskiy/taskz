#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>

using Synonymns = std::map<std::string, std::set<std::string>>;

class SynonymnsManager
{
public:
    void AddNewPair(const std::string& word1, const std::string& word2);
   
    size_t SynonymnCountByWord(const std::string& word) const;
    
    bool AreSynonymns(const std::string& word1, const std::string& word2) const;

    Synonymns GetAll() const;

private:
    Synonymns synonymns;

};

