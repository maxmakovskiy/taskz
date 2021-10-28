#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& s) 
{
    os << "{";
    bool first = true;
    for (const auto& x : s) 
    {
        if (!first) 
        {
            os << ", ";
        }

        first = false;
        os << x;
    }

    return os << "}";
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) 
{
    os << "{";
    bool first = true;
    for (const auto& x : s) 
    {
        if (!first) 
        {
            os << ", ";
        }

        first = false;
        os << x;
    }

    return os << "}";
}

template <class K, class V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) 
{
    os << "{";
    bool first = true;
    for (const auto& kv : m) 
    {
        if (!first) 
        {
            os << ", ";
        }

        first = false;
        os << kv.first << ": " << kv.second;
    }

    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) 
{
    if (t != u) 
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;

        if (!hint.empty()) 
        {
            os << " hint: " << hint;
        }

        throw std::runtime_error(os.str());
    }
}

void Assert(bool b, const std::string& hint) 
{
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) 
    {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() 
    {
        if (fail_count > 0) 
        {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const std::string& source)
{
    for (size_t i = 0, j = source.size()-1; i < source.size(); i++, j--)
    {
        if (source[i] != source[j])
            return false;
    }

    return true;
}

void TestIsPalindrom()
{
    {
        const std::string source = "madam";
        Assert(IsPalindrom(source), "IsPalindrom(" + source + ")");
    }
    {
        const std::string source = "level";
        Assert(IsPalindrom(source), "IsPalindrom(" + source + ")");
    }
    {
        const std::string source = "wasitacaroracatisaw";
        Assert(IsPalindrom(source), "IsPalindrom(" + source + ")");
    }
    {
        const std::string source = "hello";
        Assert(!IsPalindrom(source), "IsPalindrom(" + source + ")");
    }

}

void AllTest()
{
    TestRunner runner;
    runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
}

int main() 
{
    AllTest();

    return 0;
}
