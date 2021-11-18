#include "search_server.h"
#include "test.h"

using namespace std;

string ToString(const vector<string> sources)
{
    std::string result;
    
    for (const string& s : sources) {
        std::string temp = s + '\n';
        result.append(std::move(temp));
    }
    
    return result;
}

void TestBasicSearch() {
    const vector<string> docs = {
        "we are ready to go",
        "come on everybody shake you hands",
        "i love this game",
        "tell me the meaning of being lonely",
        "just keep track of it",
        "how hard could it be",
        "it is going to be legen wait for it dary legendary",
        "we dont need no education"
  };

    const string query = "we need some help";
    const string expected = "[" + query + "]: "
        + "{docid: 7, hitcount: 2} " 
        + "{docid: 0, hitcount: 1}";
    
    istringstream inDocs;
    inDocs.str(ToString(docs));
    SearchServer server(inDocs);
    
    istringstream inQuery;
    inQuery.str(query);

    ostringstream out;

    server.AddQueriesStream(inQuery, out);

    ASSERT_EQUAL(out.str(), expected); 

}

void TestBench()
{
    const vector<string> source = { // size = 8
        "we are ready to go",
        "come on everybody shake you hands",
        "i love this game",
        "tell me the meaning of being lonely",
        "just keep track of it",
        "how hard could it be",
        "it is going to be legen wait for it dary legendary",
        "we dont need no education"
    };

    vector<string> docs;
    const int MULTI = 50000; 
    for (int i = 0; i < MULTI; i++) {
        std::for_each(source.begin(), source.end(),
            [&docs](const string& s) {
                docs.push_back(s);
            });
    }

    const string query = "we need some help";
   
    istringstream inDocs;
    inDocs.str(ToString(docs));
    SearchServer server(inDocs);
    
    istringstream inQuery;
    inQuery.str(query);

    ostringstream out;
    {
        LOG_DURATION_MILLISECONDS("Bench: elements in base " 
                + to_string(MULTI)
                + "; time to work");
        server.AddQueriesStream(inQuery, out);
    }
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestBasicSearch);
    RUN_TEST(tr, TestBench);

    return 0;
}
