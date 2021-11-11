#include "test.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template <class T>
class ObjectPool 
{
public:
    T* Allocate()
    {
        if (!freeObjects.empty()) {
            T* result = freeObjects.front();
            freeObjects.pop();
            allocatedObjects.insert(result);
            return result;
        }

        T* newObj = new T;
        allocatedObjects.insert(newObj);
        return newObj;
    }

    T* TryAllocate()
    {
        if (!freeObjects.empty()) {
            T* result = freeObjects.front();
            freeObjects.pop();
            allocatedObjects.insert(result);
            return result;
        }

        return nullptr;      
    }

    void Deallocate(T* object)
    {
        auto pos = allocatedObjects.find(object);
        if (pos == allocatedObjects.end()) { 
            throw std::invalid_argument("object doesn't exist in pool");
        }

        freeObjects.push(*pos);
        allocatedObjects.erase(pos);
    }

    ~ObjectPool()
    {
        for (auto& element : allocatedObjects) { delete element; }
        
        while(!freeObjects.empty()) {
            T* temp = freeObjects.front();
            freeObjects.pop();
            delete temp;
        }
    }

private:
    std::queue<T*> freeObjects;
    std::set<T*> allocatedObjects;
};

void TestObjectPool() {
  ObjectPool<std::string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() 
{
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);

  return 0;
}
