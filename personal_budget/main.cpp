#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cmath>
#include <numeric>

#include "date.h"

enum class QueryType : int
{
    COMPUTE, EARN
};

struct Query
{
    QueryType type;
    Date beginDate;
    Date endDate;
    double value;
};

std::istream& operator>>(std::istream& is, Query& query)
{
    std::string type;
    is >> type;
    if (type == "Earn")
    {
        query.type = QueryType::EARN;
    }
    else 
    { // type == "ComputeIncome"
        query.type = QueryType::COMPUTE;
    }

    is >> query.beginDate;
    is >> query.endDate;

    if (query.type == QueryType::EARN)
    {
       is >> query.value;
    }

    return is;
}

class BudgetManager
{
public:
    BudgetManager()
    {
        budget = std::vector<double>(DAYS_COUNT, 0.0);
    }

    double ComputeIncome(const Query& query)
    {
        int startIdx = DaysDiff(Date(2000, 1, 1), query.beginDate) - 1;
        int endIdx = DaysDiff(Date(2000, 1, 1), query.endDate) - 1;

        return std::accumulate(budget.begin() + startIdx,
            budget.begin() + endIdx + 1, 0.0);
    }

    void Earn(const Query& query)
    {
        int startIdx = DaysDiff(Date(2000, 1, 1), query.beginDate) - 1;
        int endIdx = DaysDiff(Date(2000, 1, 1), query.endDate) - 1;

        double fractValue = query.value  / (endIdx - startIdx + 1);

        for (int i = startIdx; i <= endIdx; i++)
        {
            budget[i] += fractValue;
        }
    }

private:
    std::vector<double> budget;
    const int DAYS_COUNT = 36525;
};

int main()
{
    BudgetManager bm;

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        Query q;

        std::cin >> q;

        switch(q.type)
        {
        case QueryType::COMPUTE:
            std::cout << "Compute from '" << q.beginDate << "' to '" << q.endDate << "' " << bm.ComputeIncome(q) << std::endl;
            break;
        case QueryType::EARN:
            bm.Earn(q);
            break;
        }



    }


    return 0;
}
