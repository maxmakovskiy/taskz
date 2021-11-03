#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

class Figure
{
public:
    virtual std::string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Rect : public Figure
{
public:
    Rect(double width, double height)
        : name("RECT")
    {
        this->width = width;
        this->height = height;
    }

    std::string Name() override
    {
        return name;
    }

    double Perimeter() override
    {
        return (width + height) * 2;
    }

    double Area() override
    {
        return width * height;
    }

private:
    std::string name;
    double width;
    double height;

};

class Triangle : public Figure
{
public:
    Triangle(double a, double b, double c)
        : name("TRIANGLE")
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    std::string Name() override
    {
        return name;
    }

    double Perimeter() override
    {
        return a + b + c;
    }

    double Area() override
    {
       double sp = (a + b + c) / 2;
       return std::sqrt(sp * (sp - a) * (sp - b) * (sp - c));
    }

private:
    std::string name;
    double a;
    double b;
    double c;

};

class Circle : public Figure
{
public:
    Circle(double r)
        : name("CIRCLE")
    {
        this->r = r;
    }

    std::string Name() override
    {
        return name;
    }

    double Perimeter() override
    {
        return 2 * 3.14 * r; 
    }

    double Area() override
    {
        return 3.14 * r * r;
    }

private:
    std::string name;
    double r;

};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is)
{
    std::string name;
    is >> name;
    is.ignore(1);

    if (name == "RECT")
    {
        double width, height;
        is >> width;
        is.ignore(1);
        is >> height;
        return std::make_shared<Rect>(width, height);
    }

    if (name == "TRIANGLE")
    {
        double a, b, c;
        is >> a;
        is.ignore(1);
        is >> b;
        is.ignore(1);
        is >> c;
        return std::make_shared<Triangle>(a, b, c);
    }
    
    // name == "CIRCLE"
    double r;
    is >> r;

    return std::make_shared<Circle>(r);
}

int main()
{
    std::vector<std::shared_ptr<Figure>> figures;

    for (std::string line; std::getline(std::cin, line); ) 
    {
        std::istringstream is(line);
        std::string command;

        is >> command;
        if (command == "ADD") 
        {
            is >> std::ws;
            figures.push_back(CreateFigure(is));

        }
        else if (command == "PRINT") 
        {
            for (const auto& current_figure : figures) 
            {
                std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }


    return 0;
}
