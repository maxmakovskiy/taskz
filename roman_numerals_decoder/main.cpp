#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

struct RomanDigit
{
    char Character;
    int value;

    RomanDigit() {}
    RomanDigit(char Character, int value)
    {
        this->Character = Character;
        this->value = value;
    }
};

int get_weigth(int left, int right)
{
    if (left >= right)
    {
        return left + right;
    }
    else
    {
        return right - left;
    }
}

// solution("XXI"); // => 21
int roman_decoder(const std::string& source)
{
    std::vector<RomanDigit> digits;
    std::vector<std::pair<int, int>> pairs;
    int result = 0;

    std::unordered_map<char, int> valuableMap {
        {'I', 1}, {'V', 5}, {'X', 10}, 
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };

    for (int i = 0; i < source.size(); i++)
    {
        char temp = source[i];
        digits.push_back(RomanDigit(temp, valuableMap[temp]));
    }

    if (digits.size() % 2 == 0)
    {
        for (int i = 0; i < digits.size(); i += 2)
        {
            pairs.push_back(std::pair<int, int>(digits[i].value, digits[i + 1].value));
        }
    }
    else
    {
        for (int i = 0; i < digits.size() - 1; i += 2)
        {
            pairs.push_back(std::pair<int, int>(digits[i].value, digits[i + 1].value));
        }

        int odd = digits.back().value;
        if (odd != 0)
            result += odd;

    }
    
    for (int i = 0; i < pairs.size(); i++)
        result += get_weigth(pairs[i].first, pairs[i].second);

    return result;
}

int main()
{
    std::cout << "roman_decoder(XXI) -> " << roman_decoder("XXI") << std::endl;
    std::cout << "roman_decoder(VI) -> " << roman_decoder("VI") << std::endl;
    std::cout << "roman_decoder(IV) -> " << roman_decoder("IV") << std::endl;
    std::cout << "roman_decoder(II) -> " << roman_decoder("II") << std::endl;
    std::cout << "roman_decoder(XXIV) -> " << roman_decoder("XXIV") << std::endl;
    std::cout << "roman_decoder(XXIII) -> " << roman_decoder("XXIII") << std::endl;

    return 0;
}
