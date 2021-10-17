#include <iostream>
#include <vector>

std::vector<int> sq_in_rect(int lng, int wdth)
{
    std::vector<int> result;

    if (lng == wdth) return result;
   
    int less = (lng >= wdth) ? wdth : lng;
    int greather = (lng >= wdth) ? lng : wdth;
    
    while (true)
    {
        result.push_back(less);
        greather -= less;
        
        int t1 = (greather >= less) ? greather : less;
        int t2 = (greather >= less) ? less : greather;

        greather = t1;
        less = t2;

        if (greather - less == 0)
        {
            result.push_back(less);
            break;
        }
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
    std::cout << "sq_in_rect(5, 3): " << sq_in_rect(5, 3) << std::endl;
    std::cout << "sq_in_rect(3, 5): " << sq_in_rect(3, 5) << std::endl;
    std::cout << "sq_in_rect(5, 5): " << sq_in_rect(5, 5) << std::endl;


    return 0;
}
