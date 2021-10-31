#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <cmath>
#include <numeric>
#include <sstream>

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
    Date targetDate;
    double value;

};

std::istream& operator>>(std::istream& is, Query& query)
{
    std::string raw;
    is >> std::ws;
    std::getline(is, raw);

    if (raw.size() == 21)
    {
        std::stringstream ss(raw);
        query.type = QueryType::COMPUTE;

        ss >> query.beginDate;
        ss.ignore(1);
        ss >> query.endDate;

    }
    else
    {
        query.type = QueryType::EARN;

        std::stringstream ss(raw);
        ss >> query.targetDate;
        ss.ignore(1);
        ss >> query.value;
    }

    return is;
}

class BudgetManager
{
public:
    double ComputeIncome(const Query& query)
    {
//        auto firstPos = budget.find(query.beginDate);
//        auto endPos = budget.find(query.endDate);

    	auto beginPos = FindNearnessKey(query.beginDate);
     	auto endPos = FindNearnessKey(query.endDate);

        double sum = 0;

        while (beginPos != endPos)
        {
        	sum += beginPos->second;
        	beginPos++;
        }

        sum += endPos->second;

        return sum;
    }

    void Earn(const Query& query)
    {
        budget[query.targetDate] = query.value;
    }

private:
    std::map<Date, double> budget;

    std::map<Date, double>::iterator FindNearnessKey(const Date& target)
    {
    	if (budget.find(target) != budget.end()) return budget.find(target);

    	if (budget.rbegin()->first < target) return budget.rbegin().base();
    	if (budget.begin()->first > target) return budget.begin();

    	auto itUpper = budget.upper_bound(target);
    	auto itLower = std::prev(budget.upper_bound(target));

    	int dateUpperDist = DaysDiff(itUpper->first, target);
     	int dateLowerDist = DaysDiff(itLower->first, target);

     	if (dateUpperDist >= dateLowerDist)
     	{
     		return itLower;
     	}
     	else
     	{
     		return itUpper;
     	}
    }

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
