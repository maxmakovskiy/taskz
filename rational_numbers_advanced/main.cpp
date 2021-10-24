#include <iostream>
#include <numeric>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

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
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator());
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

istream& operator>>(istream& is, Rational& number)
{
    if (is.eof()) return is;

    int numerator, denominator;
    is >> numerator;
    is.ignore(1);
    is >> denominator;
    number = {numerator, denominator};

    return is;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    if (lhs.Denominator() != rhs.Denominator())
    {
        int nod_lhsNumer = lhs.Numerator() * rhs.Denominator();
        int nod_rhsNumer = rhs.Numerator() * lhs.Denominator();
        return nod_lhsNumer < nod_rhsNumer;
    }

    return lhs.Numerator() < rhs.Numerator();
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }
 
    cout << "OK" << endl;

    return 0;
}
