#include <iostream>
#include <vector>

int compute_avrg(const std::vector<int>& v)
{
    int result = 0;

    for (const int& el : v)
    {
        result += el;
    }

    return result / v.size();
}

std::vector<int> greather_then_avrg(const std::vector<int>& temperature)
{
    std::vector<int> days;
    int averange = compute_avrg(temperature);

    for (int i = 0; i < temperature.size(); i++)
    {
        if (temperature[i] > averange)
        {
            days.push_back(i); 
        }
    }

    return days;
}

std::ostream& operator<<(std::ostream& stream, const std::vector<int>& v)
{
    for (std::vector<int>::const_iterator it = v.begin();
            it != v.end(); it++)
    {
        stream << *it << " ";
    }
    stream << std::endl;
    return stream;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> temperatures(n);
    for (int& el : temperatures)
    {
        std::cin >> el;
    }
    
    std::cout << "Results:" << std::endl;
    std::vector<int> result = greather_then_avrg(temperatures);
    std::cout << result.size() << std::endl;
    std::cout << result;

    return 0;
}
