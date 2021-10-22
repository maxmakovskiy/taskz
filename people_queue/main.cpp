#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string& source)
{
    std::vector<std::string> result;
    std::string intermediate;

    for (char c : source)
    {
        if (c == ' ')
        {
            result.push_back(intermediate);
            intermediate.clear();
            continue;
        }
        intermediate.push_back(c);
    }

    result.push_back(intermediate);

    return result;
}

int main()
{
    std::vector<std::string> queue;
   
    int n;
    std::cin >> n;
    std::vector<std::string> commands(n);
    std::cin >> std::ws; // skip whitespace
    for(auto& el : commands)
    {
        std::getline(std::cin, el);
    }
    
    for (auto el : commands)
    {
        std::vector<std::string> temp = split(el);

        if(temp[0] == "WORRY")
        {
            int i = std::stoi(temp[1]);
            queue[i] = "WORRY";
        }
        else if (temp[0] == "QUIET")
        {
            int i = std::stoi(temp[1]);
            queue[i] = "QUIET";
        }
        else if (temp[0] == "WORRY_COUNT")
        {
            int counter = 0;
            for (auto el : queue)
            {
                if (el == "WORRY")
                    counter++;
            }
            std::cout << "Numbers of worry peoples in queue: " << counter << std::endl;
        }
        else if (temp[0] == "COME")
        {
            if (temp[1].size() == 1)
            {
                int newQuietPeople = std::stoi(temp[1]);
                for (int i = 0; i < newQuietPeople; i++)
                    queue.push_back("QUIET"); 
            }
            else
            {
                temp[1].erase(temp[1].begin());
                int releasePeople = std::stoi(temp[1]);
                for (int i = 0; i < releasePeople; i++)
                    queue.pop_back(); 

            } 

        }
    }

    return 0;
}
