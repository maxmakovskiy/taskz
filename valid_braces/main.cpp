#include <iostream>
#include <vector>

bool valid_braces(std::string braces) 
{
    std::vector<char> stack;

    for (char c : braces)
    {
        switch(c)
        {
        case '(':
        case '[':
        case '{':
            stack.push_back(c);
            break;
        case ')':
            if (stack.back() == '(')
                stack.pop_back();
            break;
        case ']':
            if (stack.back() == '[')
                stack.pop_back();
            break;
        case '}':
            if (stack.back() == '{')
                stack.pop_back();
            break;
        }
    }
    
    if (stack.empty())
        return true;
    
    return false;
}

int main()
{
//    std::cout << valid_braces("(){}[]") << std::endl;
//    std::cout << valid_braces("([{}])") << std::endl;
//    std::cout << valid_braces("(}") << std::endl;
//    std::cout << valid_braces("[(])") << std::endl;
//    std::cout << valid_braces("[({})](]") << std::endl;
    std::cout << valid_braces("(})") << std::endl;



    return 0;
}
