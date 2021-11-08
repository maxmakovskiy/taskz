#include "student.h"
#include "test.h"
#include "profiler.h"

#include <algorithm>

//Оптимизируйте эту функцию
bool Compare(const Student& first, const Student& second) {
    return first > second;
}

void TestComparison() {
  Student newbie {
    "Ivan", "Ivanov", {
      {"c++", 1.0},
      {"algorithms", 3.0}
    },
    2.0
  };

  Student cpp_expert {
    "Petr", "Petrov", {
      {"c++", 9.5},
      {"algorithms", 6.0}
    },
    7.75
  };

  Student guru {
    "Sidor", "Sidorov", {
      {"c++", 10.0},
      {"algorithms", 10.0}
    },
    10.0
  };
  {
    LOG_DURATION("Compare(guru, newbie)");
    ASSERT(Compare(guru, newbie));
  }

  ASSERT(Compare(guru, cpp_expert));
  ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting() {
    std::vector<Student> students {
        {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
        {"Semen", "Semenov", {{"maths", 4.}}, 4.},
        {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
        {"Petr", "Petrov", {{"maths", 3.}}, 3.},
        {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}
    };

    {
        LOG_DURATION("sort");
        std::sort(students.begin(), students.end(), Compare);
    }

    ASSERT(std::is_sorted(students.begin(), students.end(),
    [](Student first, Student second) {
      return first.Less(second);
    })
  );
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestComparison);
    RUN_TEST(tr, TestSorting);

    return 0;
}
