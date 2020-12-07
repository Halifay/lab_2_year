//
// Created by mikhail on 22.11.2020.
//

#include "matrix.h"
#include <stdexcept>
#include <type_traits>
#include <iostream>
using namespace matrix;

// code for Matrix class -----------------------------------------------------------------------------------------------
template<class T>
Matrix<T>::Matrix(int height, int length):
table(std::vector<std::vector<T>>(height, std::vector<T>(length, (T)0)))
{
    static_assert(std::is_arithmetic<T>::value, "The matrix has to be of arithmetic type!");
    if(length*height <= 0 or height < 0)
        throw std::invalid_argument("Matrix length or height must be bigger than 0.");
}

template<class T>
Matrix<T>::Matrix(std::vector<std::vector<T>> &input_vector):Matrix(input_vector.size(), input_vector[0].size())
{
    if(input_vector.size() == 0)
        throw std::invalid_argument("The input vector has to have length more than 0.");
    for(int line = 0; line < input_vector.size(); line++)
    {
        for(int num = 0; num < input_vector[line].size(); num++)
        {
            table[line][num] = input_vector[line][num];
        }

    }
    // validate();
}

template<class T>
Matrix<T>::Matrix(std::vector<T> &values):Matrix(std::vector<std::vector<T>>(1, values)) {}

// first is height, second is length
template<class T>
std::pair<int, int> Matrix<T>::get_dimensions()const
{
    std::pair<int, int> result;
    result.first = table.size();
    result.second = table[0].size();
    return result;
}

template<class T>
bool Matrix<T>::check_sizes(const Matrix<T> &first, const Matrix<T> &second)const
{
    return first.get_dimensions() == second.get_dimensions();
}

template<class T>
void Matrix<T>::validate()
{
    return;
}

template<class T>
const std::vector<T> &Matrix<T>::operator [](int i)const
{
    return table[i];
}

template<class T>
std::vector<T> &Matrix<T>::operator [](int i)
{
    return table[i];
}

template<class T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> &second)const
{
    if(!check_sizes(*this, second))
        throw std::invalid_argument("Matrices have different dimensions!");
    auto sizes = get_dimensions();
    Matrix<T> new_matrix(sizes.first, sizes.second);
    for(int i = 0; i < sizes.second; i++)
        for(int j = 0; j < sizes.first; j++)
            new_matrix[i][j] = table[i][j] + second[i][j];
    return new_matrix;
}

template<class T>
Matrix<T> Matrix<T>::operator -(const Matrix<T> &second)const
{
    if(!check_sizes(*this, second))
        throw std::invalid_argument("Matrices have different dimensions!");
    auto sizes = get_dimensions();
    Matrix<T> new_matrix(sizes.first, sizes.second);
    for(int i = 0; i < sizes.second; i++)
        for(int j = 0; j < sizes.first; j++)
            new_matrix[i][j] = table[i][j] - second[i][j];
    return new_matrix;
}

template<class T>
Matrix<T> Matrix<T>::operator *(T second)const
{
    auto sizes = get_dimensions();
    Matrix<T> new_matrix(sizes.first, sizes.second);
    for(int i = 0; i < sizes.second; i++)
        for(int j = 0; j < sizes.first; j++)
            new_matrix[i][j] = table[i][j] * second;
    return new_matrix;
}

template<class T>
Matrix<T> Matrix<T>::operator *(const Matrix<T> &second)const
{
    auto fdim = get_dimensions(), sdim = second.get_dimensions();
    if(fdim.second != sdim.first)
        throw std::invalid_argument("Matrices have incompatible sizes "
                                    "(number of columns of first matrix must be equal to number of rows of second).");
    Matrix<T> new_matrix(fdim.first, sdim.second);
    for(int i = 0; i < fdim.first; i ++)
        for(int j = 0; j < sdim.second; j++)
            for(int k = 0; k < fdim.second; k++)
                new_matrix[i][j] += (*this)[i][k] * second[k][j];
    return new_matrix;
}

template<class T>
Matrix<T> operator *(int first, const Matrix<T> &second)
{
    return second * first;
}

template<class T>
Matrix<T> Matrix<T>::hadamard(const Matrix<T> &second)const
{
    if(!check_sizes(*this, second))
        throw std::invalid_argument("Matrices have different dimensions!");
    auto sizes = get_dimensions();
    Matrix<T> new_matrix(sizes.first, sizes.second);
    for(int i = 0; i < sizes.first; i++)
        for(int j = 0; j < sizes.second; j++)
            new_matrix[i][j] = (*this)[i][j] * second[i][j];
    return new_matrix;
}

template<class T>
Matrix<T> &Matrix<T>::operator =(const Matrix<T> &second)
{
    auto dims = second.get_dimensions();
    Matrix(dims.first, dims.second);
    for(int i = 0; i < dims.first; i ++)
        for(int j = 0; j < dims.second; j++)
            table[i][j] = second[i][j];
    validate();
    return *this;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix1)
{
    for(auto line : matrix1.table)
    {
        for (auto element : line)
            out << element << ' ';
        out << '\n';
    }

    return out;
}

template<class T>
std::istream &operator>>(std::istream &in, const Matrix<T> &matrix1)
{
    int height, width;
    in >> height >> width;
    std::vector<std::vector<T>> new_table(height, std::vector<T>(width));
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            in >> new_table[i][j];
    matrix1(new_table);
}


// code for IdentityMatrix class ---------------------------------------------------------------------------------------
template<class T>
IdentityMatrix<T>::IdentityMatrix(int side):Matrix<T>(side, side)
{
    for(int i = 0; i < side; i++)
        (*this).table[i][i] = (T)1;
}

template<class T>
void IdentityMatrix<T>::validate() {}

// code for DiagonalMatrix class ---------------------------------------------------------------------------------------
template<class T>
DiagonalMatrix<T>::DiagonalMatrix(int side, T value):Matrix<T>(side, side)
{
    for(int i = 0; i < side; i++)
        this->table[i][i] = value;
}

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(std::vector<T> values):Matrix<T>(values.size(), values.size())
{
    for(int i = 0; i < values.size(); i++)
        this->table[i][i] = values[i];
}

template<class T>
void DiagonalMatrix<T>::validate() {}//TODO validation functions

// code for UpperTriangleMatrix class ----------------------------------------------------------------------------------
template<class T>
UpperTriangleMatrix<T>::UpperTriangleMatrix(std::vector<std::vector<T>> values):
Matrix<T>(values[0].size(), values[0].size())
{
    int side = values[0].size();
    for(int i = 0; i < side; i++)
        for(int j = i; j < side; j++)
            this->table[i][j] = values[i][j];
}

template<class T>
UpperTriangleMatrix<T>::UpperTriangleMatrix(int side, T value):Matrix<T>(side, side)
{
    for(int i = 0; i < side; i++)
        for(int j = i; j < side; j++)
            this->table[i][j] = value;
}

template<class T>
void UpperTriangleMatrix<T>::validate() {}//TODO validate function

// code for LowerTriangleMatrix class ---------------------------------------------------------------------------------------
template<class T>
LowerTriangleMatrix<T>::LowerTriangleMatrix(std::vector<std::vector<T>> values):
Matrix<T>(values[0].size(), values[0].size())
{
    int side = values[0].size();
    for(int i = 0; i < side; i++)
        for(int j = 0; j <= i; j++)
            this->table[i][j] = values[i][j];
}

template<class T>
LowerTriangleMatrix<T>::LowerTriangleMatrix(int side, T value):Matrix<T>(side, side)
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j <= i; j++)
            this->table[i][j] = value;
}

template<class T>
void LowerTriangleMatrix<T>::validate() {}//TODO validate function

// code for SymmetricMatrix class ---------------------------------------------------------------------------------------
template<class T>
// by default constructor will use only upper triangle half of the given array. If upper=false then it will use lower.
SymmetricMatrix<T>::SymmetricMatrix(std::vector<std::vector<T>> values, bool upper):Matrix<T>(values)
{
    // validate();
    int side = values[0].size();
    for(int i = 0; i < side; i++)
        for(int j = 0; j < i; j++)
            if(upper)
                this->table[i][j] = values[j][i];
            else
                this->table[j][i] = values[i][j];
}

template<class T>
SymmetricMatrix<T>::SymmetricMatrix(int side, T value):Matrix<T>(side, side)
{
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side; j++)
            this->table[i][j] = value;
}

template<class T>
void SymmetricMatrix<T>::validate() {}
