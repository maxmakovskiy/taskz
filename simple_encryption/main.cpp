#include <iostream>
#include <map>

std::string encrypt(const std::string& text, int n)
{
    std::string result = text;

    for(int i = 0; i < n; i++)
    {
        std::string odd;
        std::string even;

        for (std::string::size_type i = 0; i < result.size(); i++)
        {
            if (i % 2 == 0) even.push_back(result[i]);
            else odd.push_back(result[i]);
        }

        result = odd + even;
    }

    return result;
}

std::string decrypt(const std::string& encryptedText, int n)
{
    std::string result = encryptedText;

    for (int i = 0; i < n; i++)
    {
        std::string odd;
        std::string even;
        std::map<int, char> indicesAndSymbols;

        for (std::string::size_type i = 0; i < result.size(); i++)
        {
            if (i < result.size() / 2)
            {
                odd.push_back(result[i]);
            }
            else
            {
                even.push_back(result[i]);
            }
        }

        for (std::string::size_type i = 0; i < odd.size(); i++)
        {
            indicesAndSymbols[2*i] = even[i];
            indicesAndSymbols[2*i+1] = odd[i];
        }

        if (result.size() % 2 != 0)
        {
            indicesAndSymbols[result.size()-1] = even[even.size()-1];
        }

        result.clear();
        for (std::map<int, char>::iterator it = indicesAndSymbols.begin();
                it != indicesAndSymbols.end(); it++)
        {
            result.push_back(it->second); 
        }

    }

    return result;
}

int main()
{
    std::string tmp = encrypt("01234", 3);
    std::cout << "encrypt('01234', 3): " << tmp << std::endl;
    std::cout << "decrypt('" << tmp <<"', 3): " << decrypt(tmp, 3) << std::endl;

    std::string tmp2 = encrypt("012345", 1);
    std::cout << "encrypt('012345', 1): " << tmp2 << std::endl;
    std::cout << "decrypt('" << tmp2 <<"', 1): " << decrypt(tmp2, 1) << std::endl;

    std::string tmp3 = encrypt("012345", 2);
    std::cout << "encrypt('012345', 2): " << tmp3 << std::endl;
    std::cout << "decrypt('" << tmp3 <<"', 2): " << decrypt(tmp3, 2) << std::endl;

    return 0;
}
