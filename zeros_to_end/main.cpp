#include <iostream>
#include <vector>

// move_zeros({1, 0, 1, 2, 0, 1, 3}) => returns {1, 1, 2, 1, 3, 0, 0}
std::vector<int> move_zeroes(const std::vector<int>& input) {
    std::vector<int> result(input);
    int zeroCounter = 0;

    for (std::vector<int>::iterator it = result.begin();
            it != result.end();)
    {
        if (*it == 0)
        {
            zeroCounter++;
            it = result.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (int i = 0; i < zeroCounter; i++)
    {
        result.push_back(0); 
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& obj)
{
    for (auto it = obj.begin(); it != obj.end(); it++)
    {
        if (it == obj.begin()) stream << "(";
        if (it+1 == obj.end())
        {
            stream << *it << ")";
            break;
        }        
        stream << *it << " "; 
    }

    return stream;
}

int main()
{
    std::vector<int> tmp = {1, 0, 1, 2, 0, 1, 3};
    std::cout << "move_zeroes({1, 0, 1, 2, 0, 1, 3}) => " << move_zeroes(tmp) << std::endl; 

    return 0;
}
