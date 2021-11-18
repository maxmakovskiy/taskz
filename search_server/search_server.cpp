#include "search_server.h"


// add new doc to base
void
InvertedIndex::Add
(const std::string& document)
{ // O(N)
//    std::vector<std::string> words = splitToWords(document);
//    docs.reserve(words.size());
    for (const std::string& word : splitToWords(document)) 
    {
        mappings[word].push_back(docId);
    }
    docs.push_back(document);
    docId++;
}


// get list of positions(id) of obtained documents
std::list<size_t>
InvertedIndex::GetDocsIDs
(const std::string& word) const
{ // O(log(map.size()))
    if (mappings.count(word) == 0) return std::list<size_t>();
    return mappings.at(word);
}


// create server by given documents feed
SearchServer::SearchServer
(std::istringstream& document_input)
{
    UpdateDocumentBase(document_input);
}


// change current doc's base with new base by given documents feed
void
SearchServer::UpdateDocumentBase
(std::istringstream& document_input)
{ // O(N)
    if (!base.IsEmpty()) base.Clear();

    for (auto& doc : splitToDocs(document_input)) {
        base.Add(doc);
    }
}
    

// make search in current base and write result to output stream
void
SearchServer::AddQueriesStream
(std::istringstream& query_input, std::ostringstream& search_results_output)
{
    // Split query string to words
    std::vector<std::string> queryContent = splitToWords(query_input.str());
    std::vector<QueryResult> qResults;

    // Make mapping document id to relevant hit 
    std::vector<size_t> hits(base.GetAllDocs().size()); // id = index
    for (const std::string& word : queryContent) {
        for (size_t id : base.GetDocsIDs(word)) {
            hits[id]++;
        }
    }

    // Minimum 5 relevant docs for query
    qResults.reserve(5);
   
    for (int i = 0; i < 5; i++) {
        auto currentMaxIt = std::max_element(hits.begin(), hits.end());
        qResults.push_back({ std::distance(hits.begin(), currentMaxIt),
                *currentMaxIt});
        hits.erase(currentMaxIt);
    } 

    qResults.erase(std::remove_if(qResults.begin(), qResults.end(),
            [](QueryResult& q) {
                return q.hit_count == 0;
            }), qResults.end());

    // Output formatting
    PrepareOutput(search_results_output, queryContent);
    for (size_t i = 0; i < qResults.size(); i++)
    {
        if (i != 0) search_results_output << " ";
        search_results_output << qResults[i];
    }
}

void
SearchServer::PrepareOutput
(std::ostringstream& oss, const std::vector<std::string>& queryWords)
{
    oss << "[";
    for (size_t i = 0; i < queryWords.size(); i++) 
    {
        if (i == 0) {
            oss << queryWords[i];
            continue;
        }
        oss << " " << queryWords[i];
    }
    oss << "]: ";
}

std::ostringstream&
operator<<
(std::ostringstream& oss, const QueryResult& q)
{
    oss << "{docid: " << q.doc_id 
        << ", hitcount: " << q.hit_count << "}";
    return oss;
}

std::vector<std::string>
splitToWords
(const std::string& document)
{
    std::vector<std::string> result;
    std::string local;
    for (char c : document) 
    {
        if (c == ' ') {
            result.push_back(local);
            local.clear();
            continue;
        }
        local.push_back(c);
    }
    result.push_back(local);

    return result;
}

std::vector<std::string>
SearchServer::splitToDocs
(std::istringstream& document)
{ // one document represent as string with \n
    
    std::vector<std::string> result;
    for (std::string doc; std::getline(document, doc); ) 
    {
        result.push_back(doc); 
    }
    
    return result;
}

