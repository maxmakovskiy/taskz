#include "test.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

template <typename T>
class PriorityCollection 
{
public:
    using Id = size_t;

    Id Add(T object)
    {
        collection[nextId] = {0, std::move(object)};  

        return nextId++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin)
    {
        while(range_begin != range_end) {
            *ids_begin++ = Add(std::move(*range_begin++));
        }
    }

    bool IsValid(Id id) const
    {
        auto target = collection.find(id);
        if (target == collection.end()) {
            return false;
        }

        return true;
    }

    const T& Get(Id id) const
    {
        return collection.at(id).element;
    }

    void Promote(Id id)
    {
        collection[id].priority++;
    }

    pair<const T&, int> GetMax() const
    {
        auto maxElement = std::max_element(
                collection.rbegin(), collection.rend(),
                [](const auto& i1, const auto& i2){
                    return i1.second.priority < i2.second.priority;
                });

        return {maxElement->second.element,
                maxElement->second.priority};
    }

    pair<T, int> PopMax()
    {
        auto maxElement = std::max_element(
                collection.rbegin(), collection.rend(),
                [](const auto& i1, const auto& i2){
                    return i1.second.priority < i2.second.priority;
                });

        T tempVal = std::move(maxElement->second.element);
        int tempPriority = maxElement->second.priority;
        Id key = maxElement->first;

        collection.erase(key);
        return { std::move(tempVal), tempPriority };
    }

private:
    struct Item
    {
        int priority;
        T element;
    };

    Id nextId = 0;
    std::map<Id, Item> collection;

};


class StringNonCopyable : public string {
public:
  using string::string; 
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() 
{
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestSingleAdd()
{
    PriorityCollection<StringNonCopyable> strings;

    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");
    
    ASSERT_EQUAL(white_id, 0u);
    ASSERT_EQUAL(yellow_id, 1u);
    ASSERT_EQUAL(red_id, 2u);
}

void TestPromoteAndGetMax()
{
    PriorityCollection<StringNonCopyable> strings;

    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");

    strings.Promote(white_id);
    ASSERT_EQUAL(strings.GetMax().first, "white");
    ASSERT_EQUAL(strings.GetMax().second, 1);

    strings.Promote(yellow_id);
    ASSERT_EQUAL(strings.GetMax().first, "yellow");
    ASSERT_EQUAL(strings.GetMax().second, 1);
}

void TestIsValid()
{
    PriorityCollection<StringNonCopyable> strings;

    const auto white_id = strings.Add("white");

    ASSERT(!strings.IsValid(white_id+1000));
    ASSERT(strings.IsValid(white_id));
}

void TestGet()
{
    PriorityCollection<StringNonCopyable> strings;
    
    const auto white_id = strings.Add("white");

    ASSERT_EQUAL(strings.Get(white_id), "white"); 
}

void TestPopMax()
{
    PriorityCollection<StringNonCopyable> strings;
    
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto green_id = strings.Add("green");
   
    strings.Promote(white_id);
    strings.Promote(white_id);
    strings.Promote(white_id);
    strings.Promote(white_id);
    strings.Promote(green_id);
    strings.Promote(green_id);
    strings.Promote(green_id);
    strings.Promote(green_id);
    strings.Promote(yellow_id);

    auto green = strings.PopMax();
    ASSERT_EQUAL(green.first, "green");
    ASSERT_EQUAL(green.second, 4);
    
    auto white = strings.PopMax();
    ASSERT_EQUAL(white.first, "white");
    ASSERT_EQUAL(white.second, 4);

    auto yellow = strings.PopMax();
    ASSERT_EQUAL(yellow.first, "yellow");
    ASSERT_EQUAL(yellow.second, 1);

}

void TestRangeAdd()
{
    PriorityCollection<StringNonCopyable> strings;
    std::vector<StringNonCopyable> sources;
    std::vector<StringNonCopyable> sources2;
    
    sources.push_back("white");
    sources2.push_back("white");
    sources.push_back("green");
    sources2.push_back("green");
    sources.push_back("yellow");
    sources2.push_back("yellow");
    sources.push_back("grey");
    sources2.push_back("grey");

    std::vector<size_t> ids(sources.size());
    strings.Add(sources.begin(), sources.end(), ids.begin());
   
    for (size_t i = 0; i < ids.size(); i++) {
        ASSERT_EQUAL(strings.Get(ids[i]), sources2[i]); 
        ASSERT(strings.IsValid(ids[i]));
    }
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    RUN_TEST(tr, TestSingleAdd);
    RUN_TEST(tr, TestPromoteAndGetMax);
    RUN_TEST(tr, TestIsValid);
    RUN_TEST(tr, TestGet);
    RUN_TEST(tr, TestPopMax);
    RUN_TEST(tr, TestRangeAdd);

    return 0;
}
