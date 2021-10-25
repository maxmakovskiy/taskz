#include <iostream>
#include <limits>
#include <cstdint>

int main()
{
    int n, r;
    std::cin >> n >> r;
    int64_t sum = 0;

    for (int i = 0; i < n; i++)
    {
        int w, h, d;
        std::cin >> w >> h >> d;
        sum += w * h * d * r;        
    }
    
    std::cout << sum << std::endl;

    // 9223372036854775807
    // 8
    // 2147483647
    // std::cout << std::numeric_limits<int64_t>::max() << std::endl;
    // std::cout << sizeof(int64_t) << std::endl;
    // std::cout << std::numeric_limits<int>::max() << std::endl;

    return 0;
}
