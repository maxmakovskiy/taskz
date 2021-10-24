#include <iostream>
#include <vector>
#include <algorithm>

struct Image
{
    double quality;
    double freshness;
    double rating;
};

struct Params
{
    double a;
    double b;
    double c;
};

class FunctionPart
{
public:
    FunctionPart(char operation, double value)
    {
        this->operation = operation;
        this->value = value;
    }

    double Apply(double source) const
    {
        if (operation == '+')
            return source + value;
        else if (operation == '-')
            return source - value;
        else if (operation == '*')
            return source * value;
        else
            return source / value;
    }

    void Invert()
    {
        switch (operation)
        {
        case '+':
            operation = '-';
            break;
        case '-':
            operation = '+';
            break;
        case '*':
            operation = '/';
            break;
        case '/':
            operation = '*';
            break;
        }

    }

private:
    char operation;
    double value;
};

class Function
{
public:
    void AddPart(char operation, double value)
    {
        parts.push_back(FunctionPart(operation, value));
    }

    double Apply(double value) const
    {
        for (const FunctionPart& part : parts)
        {
            value = part.Apply(value);
        }

        return value;
    }

    void Invert()
    {
        for (FunctionPart& part : parts)
        {
            part.Invert();
        }

        std::reverse(begin(parts), end(parts));
    }

private:
    std::vector<FunctionPart> parts;
};

Function MakeWeightFunction(const Params& params, const Image& image)
{
    Function function;
    function.AddPart('*', params.a);
    function.AddPart('-', image.freshness * params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image)
{
    Function func = MakeWeightFunction(params, image);
    return func.Apply(image.quality);
/*
    double weight = image.quality;
    weight -= image.freshness * params.a + params.b;
    weight += image.rating * params.c;
    return weight;
*/
}

double ComputeQualityByWeight(const Params& params,
        const Image& image, double weight)
{
    Function func = MakeWeightFunction(params, image);
    func.Invert();
    return func.Apply(weight);

/*
    double quality = weight;
    quality -= image.rating * params.c;
    quality += image.freshness * params.a + params.b;
    return quality;
*/
}


int main()
{
    Image image;
    image.quality = 10;
    image.freshness = 2;
    image.rating = 6;

    Params params;
    params.a = 4;
    params.b = 2;
    params.c = 6;

    std::cout << ComputeImageWeight(params, image) << std::endl; 
    std::cout << ComputeQualityByWeight(params, image, 52) << std::endl; 

    return 0;
}
