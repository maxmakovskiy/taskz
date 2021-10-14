/*
 * 1, 1 --> "10" (1 + 1 = 2 in decimal or 10 in binary)
 * 5, 9 --> "1110" (5 + 9 = 14 in decimal or 1110 in binary)
*/

#include <string>
#include <vector>
#include <iostream>

std::string to_bin(int decimal)
{
    std::vector<int> digits;
    std::string result;

    while(decimal >= 0)
    {
        digits.push_back(decimal % 2);
        decimal /= 2; 

        if (decimal == 0)
            break;
    }

   
    while(digits.begin() != digits.end())
    {
        result.append(std::to_string(digits.back())); 
        digits.pop_back();
    }
    
    return result;
}

std::string add_binary(int a, int b)
{
    return to_bin(a+b);
}

int main()
{
    std::cout << "add_binary: " << add_binary(9, 5) << std::endl;



    return 0;
}
