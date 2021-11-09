#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "test.h"
#include "profiler.h"

class RouteManager 
{
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  int FindNearestFinish(int start, int finish) const {
    int result = std::abs(start - finish);

    // if collection doesn't have given stations - start and finish
    if (reachable_lists_.count(start) < 1) { 
        return result;
    }
    const std::set<int>& reachable_stations = reachable_lists_.at(start);
    const auto finish_pos = reachable_stations.lower_bound(finish);
    if (finish_pos != reachable_stations.end()) {
        result = std::min(result, std::abs(finish - *finish_pos));
    } 
    if (finish_pos != reachable_stations.begin()) {
        result = std::min(result, std::abs(finish - *std::prev(finish_pos)));
    }

    return result;
  }
private:
  std::map<int, std::set<int>> reachable_lists_;
};

void TestBench()
{
    RouteManager manager;
   
    {
        LOG_DURATION_MILLISECONDS("AddRoute");
        for (int i = 0, j = -60000; i < 100000; i++, j += 3) {
            manager.AddRoute(j, i);
        }
    }
    {

        LOG_DURATION_MILLISECONDS("FindNearestFinish");
        for(int i = 10000, j = -80000; i < 90000; i++, j += 2) {
            manager.FindNearestFinish(i, j);
        }
    }    

}

void TestCorrectness()
{
    RouteManager manager;
    
    manager.AddRoute(-2, 5);
    manager.AddRoute(10, 4);
    manager.AddRoute(5, 8);

    ASSERT_EQUAL(manager.FindNearestFinish(4, 10), 0);
    ASSERT_EQUAL(manager.FindNearestFinish(4, -2), 6);
    ASSERT_EQUAL(manager.FindNearestFinish(5, 0), 2);
    ASSERT_EQUAL(manager.FindNearestFinish(5, 100), 92);

}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBench);
    RUN_TEST(tr, TestCorrectness);

/*
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }
*/

  return 0;
}
