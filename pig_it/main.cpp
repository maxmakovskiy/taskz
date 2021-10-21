#include <iostream>
#include <string>
#include <vector>

enum class Category : int
{
    none = 0,
    word,
    punctuation
};

struct Token
{
    Category category;
    std::string str;
    int position;

    Token()
    {
        category = Category::none;
    }

    Token(Category category, std::string str, int position) 
    {
        this->category = category;
        this->str = str;
        this->position = position;
    }
};

Category choose_category(const std::string& source)
{
    if (source.size() == 1)
    {
        char c = source.front();
        if ((c >= 65 && c <= 90) ||
            (c >= 97 && c <= 122))
        {
            return Category::word;
        }

        return Category::punctuation;
    }


    return Category::word;
}

std::vector<Token> split(const std::string& source)
{
    std::vector<Token> result;
    std::string intermediate;
    int counter = 0;

    for (char c : source)
    {

        if (c == ' ' || c == '\0' || c == '\n')
        {
            result.push_back(Token(choose_category(intermediate), intermediate, counter));
            intermediate.clear();
            counter++;

            continue;
        }

        intermediate.push_back(c);
    }

    result.push_back(Token(choose_category(intermediate), intermediate, counter));

    return result;
}

void pig_it_once(std::string& str)
{
    std::string suffix = "ay";
    char first = str.front();
    str.push_back(first);
    str.erase(str.begin());
    str += suffix;
}

// "Pig latin is cool" => "igPay atinlay siay oolcay"
// Move the first letter of each word to the end of it, then add "ay" to the end of the word. Leave punctuation marks untouched.
std::string pig_it(const std::string& str)
{
    std::string result;
    std::vector<Token> tokens = split(str);

    for (std::vector<Token>::iterator it = tokens.begin();
            it != tokens.end(); it++)
    {
        if (it->category != Category::punctuation)
            pig_it_once(it->str);   

        if (it+1 == tokens.end())
        {
            result.append(it->str);
            break;
        }
        result.append(it->str + " ");
    }
    
    return result;
}

int main()
{
    std::cout << pig_it("Pig latin , is cool !") << std::endl;

    return 0;
}
