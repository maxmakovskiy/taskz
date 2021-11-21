#include "test.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record 
{
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

class Database 
{
public:
    bool Put(const Record& record)
    {
        if (base.count(record.id) > 0) return false;

        base[record.id] = record;
        timeToRecord.insert({record.timestamp, &base[record.id]});
        karmaToRecord.insert({record.karma, &base[record.id]});
        usernameToRecord.insert({record.user, &base[record.id]});

        return true;
    }

    const Record* GetById(const string& id) const
    {
        auto it = base.find(id);
        return ((it != base.end())
                ? &(it->second)
                : nullptr);
    }

    bool Erase(const string& id)
    {
        auto it = base.find(id);
        if (it != base.end()) 
        {
            eraseInSecondary(it->second.timestamp, timeToRecord, id);
            eraseInSecondary(it->second.karma, karmaToRecord, id);
            eraseInSecondary(it->second.user, usernameToRecord, id);
            base.erase(it); 

            return true;
        }

        return false;        
    }


    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    { // [low, high]
        rangeBy(low, high, timeToRecord, callback);
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        rangeBy(low, high, karmaToRecord, callback);
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const
    {
        rangeBy(user, user, usernameToRecord, callback);
    }

private:
    // secondary index
    multimap<int, Record*> timeToRecord;
    multimap<int, Record*> karmaToRecord;
    multimap<string, Record*> usernameToRecord;

    // primary index
    unordered_map<string, Record> base;
   
    template<typename Collection, typename K>
    void eraseInSecondary(K& key, Collection& c, const string& id) 
    {
        auto it = c.lower_bound(key);
        while(it->second->id != id) {
            it++;
        }
        c.erase(it); 
    }

    template<typename Collection, typename Key, typename Callback>
    void rangeBy(Key& lowerBound, Key& upperBound, Collection& c, Callback callback) const
    {
        auto lowerIt = c.lower_bound(lowerBound);
        auto upperIt = c.upper_bound(upperBound);
        for (; lowerIt != upperIt; lowerIt++) {
            if(!callback((*lowerIt->second))) return;
        }
    }
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma,
          [&count](const Record&) {
            ++count;
            return true;
          });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

void TestPutAndErase()
{
    Database db;
    ASSERT(db.Put({"id", "Have a hand", "not-master", 1536107260, 10}));
    ASSERT(db.Put({"id1", "Hello there", "master", 1536107260, 3}));
    ASSERT(db.Erase("id"));
    ASSERT(!db.Erase("id"));
    ASSERT(db.Erase("id1"));
    ASSERT(!db.Erase("id1"));
}

void TestRangeTimestamp()
{
  const int start = 10;
  const int finish = 50;

  Database db;

  for (int i = 1; i <= 10; i++) 
  {
      string str = to_string(i);
      db.Put({"id" + str,
              "Hello there " + str,
              "master " + str,
              i*10, i});
  }

  int count = 0;
  db.RangeByTimestamp(start, finish,
          [&count](const Record&) {
            ++count;
            return true;
          });
  ASSERT_EQUAL(5, count);
  
  count = 0;
  db.RangeByTimestamp(start, finish,
          [&count](const Record& r) {
            if (r.timestamp == 40) return false;
            ++count;
            return true;
          });
  ASSERT_EQUAL(3, count);

}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    RUN_TEST(tr, TestPutAndErase);
    RUN_TEST(tr, TestRangeTimestamp);

  return 0;
}
