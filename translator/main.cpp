#include "test.h"
#include <string>
#include <map>
#include <deque>
#include <string_view>


class Translator 
{
public:
    void Add(std::string_view source, std::string_view target)
    {
        std::string_view localSource = makeLocalCopy(source);
        std::string_view localTarget = makeLocalCopy(target);

        sourceToTarget[localSource] = localTarget;
        targetToSource[localTarget] = localSource;
    }

    std::string_view TranslateForward(std::string_view source) const
    {
        if (!contains(source, sourceToTarget)) return std::string_view();
        return sourceToTarget.at(source); 
    }

    std::string_view TranslateBackward(std::string_view target) const
    {
        if (!contains(target, targetToSource)) return std::string_view();
        return targetToSource.at(target);
    }

private:
    std::map<std::string_view, std::string_view> sourceToTarget;
    std::map<std::string_view, std::string_view> targetToSource;
    std::deque<std::string> realStrings;

    std::string_view makeLocalCopy(std::string_view item)
    {
        std::string& temp = realStrings.emplace_back(
                std::string(item.begin(), item.end()));
        return std::string_view(temp);
    }

    bool contains(std::string_view key,
            const std::map<std::string_view, std::string_view>& c) const
    {
        return c.find(key) != c.end();
    }
};

void TestSimple() 
{
  Translator translator;
  translator.Add(std::string("okno"), std::string("window"));
  translator.Add(std::string("stol"), std::string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() 
{
  TestRunner tr;
  RUN_TEST(tr, TestSimple);

  return 0;
}
