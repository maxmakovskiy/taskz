#include "test.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>


template <typename Iterator>
class Page
{
public:
    Page(Iterator first, Iterator last)
    {
        this->first = first;
        this->last = last;
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

    size_t size() const
    {
        return last - first;
    }

private:
    Iterator first;
    Iterator last;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
        : mBegin(begin)
        , mEnd(end)
        , page_size(page_size)
    {
        page_count = (end - begin) / page_size;
        if ((end-begin) % page_size != 0) page_count++;
        
        slice();
    }
    
    auto begin() const
    {
        return pages.begin();
    }

    auto end() const
    {
        return pages.end();
    }

    size_t size() const
    {
        return page_count;
    }


private:
    Iterator mBegin;
    Iterator mEnd;
    size_t page_size;
    size_t page_count;
    std::vector<Page<Iterator>> pages;

    void slice()
    {
        auto first = mBegin;
        auto last = mBegin + page_size;

        for (size_t i = 0; i < page_count; i++)
        {
            pages.push_back(Page(first, last));
            first = last;
            
            if (last + page_size > mEnd)
            {
                last += (mEnd-mBegin) - ((static_cast<int>(i) + 1) * page_size);
                continue;
            }

            last += page_size;
        }

    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

void TestPageCounts() 
{
    std::vector<int> v(15);
    
    std::iota(v.begin(), v.end(), 1);

    ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
    ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
    ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
    ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
    ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
    ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}


void TestLooping() 
{
    std::vector<int> v(15);
    std::iota(std::begin(v), std::end(v), 1);

    Paginator<std::vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
    std::ostringstream os;
    for (const auto& page : paginate_v) {
        for (int x : page) {
            os << x << ' ';
        }
        os << '\n';
    }

    ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() 
{
    std::vector<std::string> vs = {"one", "two", "three", "four", "five"};
    for (auto page : Paginate(vs, 2)) {
        for (auto& word : page) {
            word[0] = toupper(word[0]);
        }
    }

    const std::vector<std::string> expected = {"One", "Two", "Three", "Four", "Five"};
    ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() 
{
    std::string letters(26, ' ');

    Paginator letters_pagination(letters.begin(), letters.end(), 11);
    std::vector<size_t> page_sizes;
    for (const auto& page : letters_pagination) {
        page_sizes.push_back(page.size());
    }

    const std::vector<size_t> expected = {11, 11, 4};
    ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() 
{
    const std::string letters = "abcdefghijklmnopqrstuvwxyz";

    std::vector<std::string> pages;
    for (const auto& page : Paginate(letters, 10)) {
        pages.push_back(std::string(page.begin(), page.end()));
    }

    const std::vector<std::string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
    ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() 
{
    std::vector<int> v(22);
    std::iota(begin(v), end(v), 1);

    std::vector<std::vector<int>> lines;
    for (const auto& split_by_9 : Paginate(v, 9)) {
        for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
            lines.push_back({});
            for (int item : split_by_4) {
                lines.back().push_back(item);
            }
        }
    }

    const std::vector<std::vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
    };
    ASSERT_EQUAL(lines, expected);
}

int main() 
{
    TestRunner tr;

    RUN_TEST(tr, TestPageCounts);
    RUN_TEST(tr, TestLooping);
    RUN_TEST(tr, TestModification);
    RUN_TEST(tr, TestPageSizes);
    RUN_TEST(tr, TestConstContainer);
    RUN_TEST(tr, TestPagePagination);

    return 0;
}

