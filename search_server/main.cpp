#include "search_server.h"
#include "test.h"

using namespace std;

std::string ToString(const vector<string> sources)
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

int main() 
{
    TestRunner tr;

//  RUN_TEST(tr, TestSerpFormat);
//  RUN_TEST(tr, TestTop5);
//  RUN_TEST(tr, TestHitcount);
//  RUN_TEST(tr, TestRanking);
    RUN_TEST(tr, TestBasicSearch);

    return 0;
}
