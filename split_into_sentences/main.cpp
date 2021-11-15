#include "test.h"

#include <vector>
#include <algorithm>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) 
{
    vector<Sentence<Token>> result;
    
    tokens.erase(std::unique(tokens.begin(), tokens.end()), tokens.end());

    Sentence<Token> local;
    for (auto& token : tokens) {
       if (token.IsEndSentencePunctuation()) {
            local.push_back(std::move(token));
            result.push_back(std::move(local));
        } else {
            local.insert(std::find_if(local.begin(), local.end(),
                        [](const Token& t) {
                            return t.IsEndSentencePunctuation();
                        })
                    , std::move(token));
        }
    }
    if (!local.empty()) {
        result.push_back(std::move(local));
    }

    return result;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);

    return 0;
}
