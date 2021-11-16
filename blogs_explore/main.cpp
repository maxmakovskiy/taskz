#include "test.h"
#include "profiler.h"

#include <map>
#include <string>
#include <iostream>
#include <future>
#include <iterator>
#include <functional>

using namespace std;

struct Stats 
{
    map<string, int> word_frequences;

    void operator+=(const Stats& other)
    {
        for (const auto& [key, val] 
                : other.word_frequences) 
        {
             word_frequences[key] += val;
        }
    }
};

std::vector<std::string_view> slice(string_view source)
{
    std::vector<std::string_view> result;
    
    for (;;) {
        size_t space_pos = source.find(' ');
        result.push_back(source.substr(0, space_pos));     

        if (space_pos == source.npos) {
            break;
        } else {
            source.remove_prefix(space_pos+1);
        }
    }

    return result;
}

/*
vector<string> split(const string& source)
{
    istringstream iss(source);
    return { istream_iterator<string>(iss), istream_iterator<string>() };
}
*/

Stats
ExploreLine
(const set<string>& key_words, const string& line) 
{
    Stats s;
/*     
    for (const auto& word : split(line)) {
        if (key_words.count(word) > 0) {
            s.word_frequences[word]++;
        }
    }
*/   
    for (const string_view& word : slice(line)) {
        string temp(word.begin(), word.end());
        if (key_words.count(temp) > 0) {
            s.word_frequences[std::string(word)]++;
        }
    }

    return s;
}

Stats
ExploreBatch
(const set<string>& key_words, vector<string> batch) 
{
    Stats s;
    
    for (const string& line : batch) {
        s += ExploreLine(key_words, line);
    }

    return s;
}

Stats
ExploreKeyWordsSingleThread
(const set<string>& key_words, istream& input) 
{
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats
ExploreKeyWords
(const set<string>& key_words, istream& input) 
{
    vector<future<Stats>> fs;
    Stats result;
    

    vector<string> batch;
    size_t batchSize = 700;
    batch.reserve(batchSize);

    for (string line; getline(input, line);) {
        batch.push_back(move(line));
        if (batch.size() >= batchSize) {
            // need to make move 
            // cause next step is .clear()
            // and current thread doesn't compute stats
            // and OS scheduler switch evaluation to another process
            fs.push_back(async(ExploreBatch, ref(key_words), move(batch))); 
            batch.clear();
        }
    }

    // if lineCount % batchSize != 0
    // then batch has unprocessed elements
    if (!batch.empty()) {
        result += ExploreBatch(key_words, move(batch));
    }
    
    for (auto& f : fs) {
        result += f.get();
    }

    return result;
}

void TestAddingStats()
{
    Stats s1;
    s1.word_frequences = {
        {"yangle", 4},
        {"sucks", 1}
    };

    Stats s2;
    s2.word_frequences = {
       {"yangle", 2},
       {"rocks", 2},
    };


    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}
    };
 
    s1 += s2;
    ASSERT_EQUAL(s1.word_frequences, expected);
}

void TestSlice()
{
    const string source = "this new yangle service really rocks";
    const vector<string_view> expected = { "this", "new", "yangle", "service", "really", "rocks"};

    vector<string_view> result = slice(source);
    ASSERT_EQUAL(result.size(), expected.size());

    for (size_t i = 0; i < result.size(); i++)
    {
        ASSERT_EQUAL(result[i], expected[i]);
    }
}

void TestExploreLine()
{
    const set<string> key_words = {"yangle", "rocks"};
    const string source = "this new yangle service really rocks";
    const map<string, int> expected = {
        { "yangle", 1},
        { "rocks", 1}
    };
    
    ASSERT_EQUAL(ExploreLine(key_words, source).word_frequences, expected);
}

void TestSingleThread()
{
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWordsSingleThread(key_words, ss);

  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestMultiThread()
{
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;

  for (int i = 0; i < 1000; i++) {
      ss << "this new yangle service really rocks\n";
      ss << "It sucks when yangle isn't available\n";
      ss << "10 reasons why yangle is the best IT company\n";
      ss << "yangle rocks others suck\n";
      ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
  }

  Stats stats;
  {
    LOG_DURATION_MILLISECONDS("Multithreads");
    stats = ExploreKeyWords(key_words, ss);
  }

  const map<string, int> expected = {
    {"yangle", 6000},
    {"rocks", 2000},
    {"sucks", 1000}
  };

  ASSERT_EQUAL(stats.word_frequences, expected);

}

int main() 
{
  TestRunner tr;
  RUN_TEST(tr, TestAddingStats);
  RUN_TEST(tr, TestSlice);
  RUN_TEST(tr, TestExploreLine);
  RUN_TEST(tr, TestSingleThread);
  RUN_TEST(tr, TestMultiThread);

  return 0;
}
