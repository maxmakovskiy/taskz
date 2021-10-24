#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>


class Matrix
{
public:
    Matrix()
    {
        rowsNumber = 0;
        colomnsNumber = 0;
    }

    Matrix(int rowsNumber, int colsNumber)
    {
        Reset(rowsNumber, colsNumber);
    }

    void Reset(int rowsNumber, int colomnsNumber)
    {
        if (rowsNumber < 0 || colomnsNumber < 0)
        {
            throw std::out_of_range("new dimensions must be do not than 0");
        }
        
        this->rowsNumber = rowsNumber;
        this->colomnsNumber = colomnsNumber;
        content.assign(rowsNumber, std::vector<int>(colomnsNumber));
    }

    int At(int iRow, int jCol) const
    {
        return content.at(iRow).at(jCol);
    }

    int& At(int iRow, int jCol)
    {
        return content.at(iRow).at(jCol);
    }

    int GetNumRows() const
    {
        return rowsNumber;
    }

    int GetNumColomns() const
    {
        return colomnsNumber;
    }

private:
    std::vector<std::vector<int>> content;
    int rowsNumber;
    int colomnsNumber;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    if ((lhs.GetNumRows() != rhs.GetNumRows()) ||
        (lhs.GetNumColomns() != rhs.GetNumColomns()))
    {
        throw std::invalid_argument("matrices are not equal");
    }

    Matrix result(lhs.GetNumRows(), lhs.GetNumColomns());

    for (int i = 0; i < result.GetNumRows(); i++)
    {
        for (int k = 0; k < result.GetNumColomns(); k++)
        {
            result.At(i, k) = lhs.At(i, k) + rhs.At(i, k); 
        }
    }
    
    return result;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    if ((lhs.GetNumRows() != rhs.GetNumRows()) ||
        (lhs.GetNumColomns() != rhs.GetNumColomns()))
    {
        return false; 
    }

    for (int i = 0; i < lhs.GetNumRows(); i++)
    {
        for (int k = 0; k < lhs.GetNumColomns(); k++)
        {
            if (lhs.At(i, k) != rhs.At(i, k))
                return false;
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (int i = 0; i < matrix.GetNumRows(); i++)
    {
        for (int k = 0; k < matrix.GetNumColomns(); k++)
        {
            os << matrix.At(i, k) << " ";
        }
        os << std::endl;
    }
    
    return os;
}

void PopulateMatrix(Matrix& matrix)
{
    for (int i = 0; i < matrix.GetNumRows(); i++)
    {
        for (int k = 0; k < matrix.GetNumColomns(); k++)
        {
            matrix.At(i, k) = i + k;
        }
    }
}

int main() {
    Matrix one(3, 3);
    Matrix two(3, 3);

    PopulateMatrix(one);
    PopulateMatrix(two);
    
    Matrix result = one+two;

    std::cout << result;
    std::cout << (one == two) << std::endl;
    std::cout << (result == two) << std::endl;

    return 0;
}
