#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& s) 
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
ostream& operator<<(ostream& os, const set<T>& s) 
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
ostream& operator<<(ostream& os, const map<K, V>& m) 
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
void AssertEqual(const T& t, const U& u, const string& hint = {}) 
{
    if (t != u) 
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;

        if (!hint.empty()) 
        {
            os << " hint: " << hint;
        }

        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) 
{
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) 
    {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() 
    {
        if (fail_count > 0) 
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        if (numerator < 0 && denominator < 0)
        {
            numerator = -1 * numerator;
            denominator = -1 * denominator;
        }
        else if (denominator < 0)
        {
            numerator = -1 * numerator;
            denominator = -1 * denominator;
        }

        int nod = gcd(numerator, denominator);
        if (nod == 1)
        {
            this->numerator = numerator;
            this->denominator = denominator;
        }
        else
        {
            this->numerator = numerator / nod;
            this->denominator = denominator / nod;
        }
    }

    int Numerator() const {
        return numerator; 
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;

};

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator(),
            lhs.Denominator() * rhs.Numerator());
}

ostream& operator<<(ostream& os, const Rational& number)
{
    os << number.Numerator() << "/" << number.Denominator();
    return os;
}

void TestCreateRational()
{
    {
        Rational number;
        AssertEqual(number.Numerator(), 0, "creation: numerator 0");
        AssertEqual(number.Denominator(), 1, "creation: denominator 1");
    }
    {
        Rational number(2, 3);
        AssertEqual(number.Numerator(), 2, "creation: numerator 2");
        AssertEqual(number.Denominator(), 3, "creation: denominator 3");
    }
    {
        Rational number(4, 6);
        AssertEqual(number.Numerator(), 2, "creation: numerator 4 => 2");
        AssertEqual(number.Denominator(), 3, "creation: denominator 6 => 3");
    }
}

void TestAddition()
{
    {
        Rational num1(1, 3);
        Rational num2(4, 3);
        Rational num3 = num1 + num2;
        AssertEqual(num3.Numerator(), 5, "addition: numerator 5");
        AssertEqual(num3.Denominator(), 3, "addition: denominator 3");
    }
    {
        Rational num1(1, 3);
        Rational num2(1, 3);
        Rational num3 = num1 + num2;
        AssertEqual(num3.Numerator(), 2, "addition: numerator 2");
        AssertEqual(num3.Denominator(), 3, "addition: denominator 3");
    }
    {
        Rational num1(1, 3);
        Rational num2(2, 3);
        Rational num3 = num1 + num2;
        AssertEqual(num3.Numerator(), 1, "addition: numerator 1");
        AssertEqual(num3.Denominator(), 1, "addition: denominator 1");
    }
}

void TestSubtraction()
{
    {
        Rational num1(4, 3);
        Rational num2(2, 3);
        Rational num3 = num1 - num2;
        AssertEqual(num3.Numerator(), 2, "subtraction: numerator 2");
        AssertEqual(num3.Denominator(), 3, "subtraction: denominator 3");
    }
    {
        Rational num1(4, 3);
        Rational num2(5, 2);
        Rational num3 = num1 - num2;
        AssertEqual(num3.Numerator(), -7, "subtraction: numerator -7");
        AssertEqual(num3.Denominator(), 6, "subtraction: denominator 6");
    }
    {
        Rational num1(1, 5);
        Rational num2(4, 5);
        Rational num3 = num1 - num2;
        AssertEqual(num3.Numerator(), -3, "subtraction: numerator -3");
        AssertEqual(num3.Denominator(), 5, "subtraction: denominator 5");
    }
    {
        Rational num1(7, 6);
        Rational num2(9, 5);
        Rational num3 = num1 - num2;
        AssertEqual(num3.Numerator(), -19, "subtraction: numerator -19");
        AssertEqual(num3.Denominator(), 30, "subtraction: denominator 30");
    }
}

void TestEqual()
{
    {
        Rational num1(1, 6);
        Rational num2(1, 6);
        Assert(num1 == num2, "equal: 1/6 == 1/6");
    }
    {
        Rational num1(2, 3);
        Rational num2(4, 6);
        Assert(num1 == num2, "equal: 2/3 == 4/6");
    }
    {
        Rational num1(2, 3);
        Rational num2(5, 6);
        Assert(!(num1 == num2), "equal: 2/3 == 5/6");
    }
}

void TestMultiplication()
{
    {
        Rational num1(1, 3);
        Rational num2(9, 5);
        Rational num3 = num1 * num2;
        AssertEqual(num3.Numerator(), 3, "muliplication: numerator 3");
        AssertEqual(num3.Denominator(), 5, "muliplication: denominator 5");
    }
    {
        Rational num1(-4, 3);
        Rational num2(1, 5);
        Rational num3 = num1 * num2;
        AssertEqual(num3.Numerator(), -4, "muliplication: numerator -4");
        AssertEqual(num3.Denominator(), 15, "muliplication: denominator 15");
    }
}

void TestDivide()
{
    {
        Rational num1(4, 3);
        Rational num2(6, 5);
        Rational num3 = num1 / num2;
        AssertEqual(num3.Numerator(), 10, "divide: numerator 10");
        AssertEqual(num3.Denominator(), 9, "divide: denominator 9");
    }
    {
        Rational num1(4, 3);
        Rational num2(-6, 5);
        Rational num3 = num1 / num2;
        AssertEqual(num3.Numerator(), -10, "divide: numerator -10");
        AssertEqual(num3.Denominator(), 9, "divide: denominator 9");
    }
}

void TestOutput()
{
    {
        stringstream stream;

        Rational number(4, 3);
        stream << number;

        AssertEqual(stream.str(), "4/3", "output: 4/3");
    }
    {
        stringstream stream;

        Rational number(6, 4);
        stream << number;

        AssertEqual(stream.str(), "3/2", "output: 3/2");
    }
    {
        stringstream stream;

        Rational number(-4, -3);
        stream << number;

        AssertEqual(stream.str(), "4/3", "output: 4/3");
    }
    {
        stringstream stream;

        Rational number(-4, 3);
        stream << number;

        AssertEqual(stream.str(), "-4/3", "output: -4/3");
    }
}

void AllTest()
{
    TestRunner runner;
    runner.RunTest(TestCreateRational, "TestCreateRational");
    runner.RunTest(TestAddition, "TestAddition");
    runner.RunTest(TestSubtraction, "TestSubtraction");
    runner.RunTest(TestEqual, "TestEqual");
    runner.RunTest(TestMultiplication, "TestMultiplication");
    runner.RunTest(TestDivide, "TestDivide");
    runner.RunTest(TestOutput, "TestOutput");
}

int main() 
{
    AllTest();

    return 0;
}
