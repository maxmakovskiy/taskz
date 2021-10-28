#pragma once

#include <iostream>
#include <exception>
#include <sstream>
#include <map>
#include <set>

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const std::map<Key, Value> m)
{
    if (m.size() == 0) return os;

    os << "{";
    int i = 0;
    for (const auto& el : m)
    {
        if (i+1 == m.size())
        {
            os <<  "(" << el.first << ": " << el.second << ")}";
            break;
        }

        os <<  "(" << el.first << ": " << el.second << "), ";
        i++;
    }
    
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> s)
{
    if (s.size() == 0) return os;
   
    os << "[";

    size_t i = 0;
    for (const T& el : s)
    {
        if (i+1 == s.size())
        {
            os << el << "]";
            break;
        }

        os << el << ", ";

        i++;
    }
    
    return os;
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " HINT: " << hint;
        throw std::runtime_error(os.str()); 
    }
}

void Assert(bool b, const std::string& hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    TestRunner()
    {
        errorCounter = 0; 
    }

    ~TestRunner()
    {
        if (errorCounter > 0)
        {
            std::cerr << errorCounter << " test failed. Terminate" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    template <typename TestFunc>
    void RunTest(TestFunc func, const std::string& testName)
    {
        try
        {
            func();
            std::cerr << testName << " OK" << std::endl;
        }
        catch (std::runtime_error& e)
        {
            errorCounter++;
            std::cerr << testName << " fail: " << e.what() << std::endl;
        }
    }

private:
    int errorCounter;
};

