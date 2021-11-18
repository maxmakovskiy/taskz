#pragma once

#include <list>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include "profiler.h"


// InvertedIndex - data structure
// that save for each word - list of positions in obtained documents
class InvertedIndex 
{
public:
    // add new doc to base
    void Add(const std::string& document);

    // get list of positions(id) of obtained documents
    std::list<size_t> GetDocsIDs(const std::string& word) const;

    // get document from base by id
    inline const std::string& GetDocument(size_t id) const 
    {
        return docs[id];
    }

    inline const std::vector<std::string>& GetAllDocs()
    {
        return docs;
    }

    inline void Clear() 
    {
        docs.clear();
        mappings.clear();
    }

    inline bool IsEmpty() const
    {
        return is_empty;
    }

private:
    std::map<std::string, std::list<size_t>> mappings;
    std::vector<std::string> docs;
    bool is_empty = true;
    size_t docId = 0;

};

class SearchServer 
{
public:
    // create server with empty base
    SearchServer() = default;

    // create server by given documents feed
    explicit SearchServer(std::istringstream& document_input);

    // change current doc's base with new base by given documents feed
    void UpdateDocumentBase(std::istringstream& document_input);
    
    // make search in current base and write result to output stream
    void AddQueriesStream(std::istringstream& query_input,
            std::ostringstream& search_results_output);

private:
    InvertedIndex base;
   
    void PrepareOutput(std::ostringstream& oss,
            const std::vector<std::string>& queryWords);

    std::vector<std::string> splitToDocs(std::istringstream& document);

};

std::vector<std::string> splitToWords(const std::string& document);

/* @brief Data structure, that represent
 * more relevant doc from base for given query
 * @field doc_id    Document identifier
 * @field hit_count Count of source word instances in document
 * */
 
struct QueryResult
{
    size_t doc_id;
    size_t hit_count;
};

std::ostringstream& operator<<(std::ostringstream& oss, const QueryResult& q);

