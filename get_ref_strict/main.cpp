#include <iostream>
#include <map>


template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& m, Key k)
{
    return m[k];
}

int main()
{
    std::map<int, std::string> m = {{0, "value"}};
    std::string& item = GetRefStrict(m, 0);

    item = "newvalue";

    std::cout << m[0] << std::endl; 

    return 0;
}
