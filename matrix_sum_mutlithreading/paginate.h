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

