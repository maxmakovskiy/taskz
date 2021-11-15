#pragma once
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
        length = std::distance(first, last);
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
        return length;
    }

private:
    Iterator first;
    Iterator last;
    size_t length;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
        : mBegin(begin)
        , mEnd(end)
        , page_size(page_size)
    {
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
        return pages.size();
    }


private:
    Iterator mBegin;
    Iterator mEnd;
    size_t page_size;
    size_t page_count;
    std::vector<Page<Iterator>> pages;

    void slice()
    {
        for (size_t remained = std::distance(mBegin, mEnd); remained > 0;) {
            size_t currentPageSize = std::min(page_size, remained);
            auto currentEnd = std::next(mBegin, currentPageSize);

            pages.push_back(Page(mBegin, currentEnd));
            
            remained -= currentPageSize;
            mBegin = currentEnd;
        }
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

