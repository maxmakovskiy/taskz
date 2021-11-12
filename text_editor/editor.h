#pragma once

class Editor
{
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor()
        : cursor(0)
    {
    }

    void Left()
    {
        if (content.empty() || cursor == 0) return;

        cursor--;
    }

    void Right()
    {
        if (content.empty() || cursor == content.size()) return;

        cursor++;
    }

    void Insert(char token)
    {
        content.insert(content.begin() + cursor, token); 
        Right();
    }

    void Paste()
    {
        for (char c : buffer) {
            Insert(c);
        }
    }

    void Cut(size_t tokens = 1)
    {
        for (size_t i = 0; i < tokens; i++)
        {
            buffer += content[cursor];
            content.erase(cursor, 1);
        }
    }

    void Copy(size_t tokens = 1)
    {
        for (size_t i = 0;
                i < std::min(tokens, buffer.size()-1); 
                i++) {
            Insert(buffer[i]);
        }
        
    }

    std::string GetText() const
    {
        return content;
    }

private:
    std::string content;
    std::string buffer;
    size_t cursor;
};


