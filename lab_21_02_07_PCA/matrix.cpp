//
// Created by mikhail on 22.11.2020.
//

#include "matrix.h"
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace matrix;
const double eps = 1e-6;
const int max_length = 511;

// code for Matrix class -----------------------------------------------------------------------------------------------
template<class T>
Matrix<T>::Matrix(){}

template<class T>
Matrix<T>::Matrix(int height, int length, int value):
table(std::vector<std::vector<T>>(height, std::vector<T>(length, (T)value)))
{
    static_assert(std::is_arithmetic<T>::value, "The matrix has to be of arithmetic type!");
    if(length*height <= 0 or height < 0)
        throw std::invalid_argument("Matrix length or height must be bigger than 0.");
}

template<class T>
Matrix<T>::Matrix(int height, int length, int rseed, int max):Matrix(height, length)
{
    std::srand(rseed);
    for(int i = 0; i < height; i++)
        for(int j = 0; j < length; j++)
            table[i][j] = (T)(std::rand()%max);
}

template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &input_vector):
Matrix(input_vector.size(), input_vector[0].size())
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
Matrix<T>::Matrix(const std::vector<T> &values):Matrix(std::vector<std::vector<T>>(1, values)) {}

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
T Matrix<T>::Gauss(int from_up, int from_left)
{
    auto sizes = get_dimensions();
    if(sizes.first - from_up < 1 || sizes.second - from_left < 1)
        return 1;
    T result = 1;
    bool is_null = true;
    for(int i = from_up; i < sizes.first; i++)
    {
        if(double(abs(table[i][from_left])) > eps)
        {
            if(i == from_up)
                result = 1;
            else
                result = -1;
            is_null = false;
            std::swap(table[i], table[from_up]);
            break;
        }
    }
    if(is_null)
    {
        return 0*Gauss(from_up, from_left + 1);
    }
    else
    {
        for(int i = from_up + 1; i < sizes.first; i++)
        {
            T coefficient = table[i][from_left]/table[from_up][from_left];
            for(int j = from_left; j < sizes.second; j++)
            {
                table[i][j] -= table[from_up][j] * coefficient;
            }
        }
        result *= table[from_up][from_left] * Gauss(from_up + 1, from_left + 1);
        for(int j = sizes.second-1; j>=from_left; j--)
        {
            table[from_up][j] /= table[from_up][from_left];
        }
    }
    return result;
}

template<class T>
T Matrix<T>::determinant()const
{
    auto sizes = get_dimensions();
    if(sizes.first != sizes.second)
        return 0;
    Matrix<T> for_det(table);
    T res = for_det.Gauss();
    return res;
}

template<class T>
Matrix<T> Matrix<T>::Transpose()
{
    auto sizes = get_dimensions();
    std::vector<std::vector<T>> new_table;
    new_table.resize(sizes.second, std::vector<T>(sizes.first));
    for(int i = 0; i < sizes.first; i++)
    {
        for(int j = 0; j < sizes.second; j++)
        {
            new_table[j][i] = table[i][j];
        }
    }
    Matrix<T> transposed_matrix(new_table);
    return transposed_matrix;
}

template<class T>
int Matrix<T>::rank()const
{
    Matrix<T> new_matrix(table);
    new_matrix.Gauss();
    auto sizes = get_dimensions();
    int rank = 0;
    for(int i = 0; i < sizes.first; i++)
    {
        for(int j = i; j < sizes.second; j++)
        {
            if(abs(new_matrix[i][j]) > eps)
            {
                rank++;
                break;
            }
            return rank;
        }
    }
    return rank;
}

template<class T>
Matrix<T> Matrix<T>::inverse() const
{
    auto sizes = get_dimensions();
    if(abs(determinant()) < eps)
    {
        return Matrix<T>(sizes.first, sizes.second);
    }
    Matrix<T> inverted(table);

    for(int i = 0; i < sizes.first; i++)
    {
        // inverted.table.resize(sizes.second * 2);
        for(int j = sizes.second; j < sizes.second * 2; j++)
        {
            if(i == j - sizes.second)
                inverted.table[i].push_back(1);
            else
                inverted.table[i].push_back(0);
        }
    }
    inverted.Gauss();
    for(int i = 0; i < sizes.first; i++)
    {
        for(int j = i-1; j >= 0; j--)
        {
            T ratio = inverted.table[j][i]/inverted.table[i][i];
            for(int k = i; k < sizes.second*2; k++)
            {
                inverted.table[j][k] -= ratio * inverted.table[i][k];
            }
        }
    }
    std::vector<std::vector<T>> result;
    result.resize(sizes.first);
    for(int i = 0; i < sizes.first; i++)
    {
        result[i] = std::vector<T>(inverted.table[i].begin() + sizes.second, inverted.table[i].end());
    }

    return Matrix<T>(result);
}

template<class T>
T Matrix<T>::scalar(const Matrix<T> &second) const
{
    auto sizes1 = get_dimensions(), sizes2 = second.get_dimensions();
    if(sizes1 != sizes2 || sizes1.first != 1)
        throw std::invalid_argument("Incompatible sizes for vector scalar operation.");
    T result = 0;
    for(int i = 0; i < sizes1.second; i++)
    {
        result += table[0][i] * second[0][i];
    }
    return result;
}

template<class T>
T Matrix<T>::v_norm_euc() const
{
    auto sizes = get_dimensions();
    if(sizes.first != 1 || sizes.second < 0)
        throw std::invalid_argument("Vector has have one row with at least 1 number in it.");
    T result = 0;
    for(T coordinate : table[0])
    {
        result += coordinate*coordinate;
    }
    return std::sqrt(result);
}

template<class T>
T Matrix<T>::v_norm_max() const
{
    auto sizes = get_dimensions();
    if(sizes.first != 1 || sizes.second < 0)
        throw std::invalid_argument("Vector has have one row with at least 1 number in it.");
    T result = table[0][0];
    for(T coordinate : table[0])
    {
        result = std::max(result, coordinate);
    }
    return result;
}

template<class T>
T Matrix<T>::sum() const
{
    T result = 0;
    auto sizes = get_dimensions();
    for(int i = 0; i < sizes.first; i++)
    {
        for(int j = 0; j < sizes.second; j++)
        {
            result += table[i][j];
        }
    }
    return result;
}

template<class T>
double Matrix<T>::angle(const Matrix<T> &second) const
{
    T product = scalar(second), lenf = v_norm_euc(), lens = second.v_norm_euc();
    return std::acos(product/(lenf*lens));
}

template<class T>
T Matrix<T>::m_form_frb() const
{
    T result = 0;
    for(auto line : table)
        for(T value : line)
            result += value * value;
    return std::sqrt(result);
}


//input/output

template<class T>
bool Matrix<T>::read_text(std::string &filename)
{
    std::fstream input;
    input.open(filename);
    if(!input.is_open())
        return false;
    input >> *this;
    input.close();
    return true;
}

template<class T>
bool Matrix<T>::write_text(std::string &filename)
{
    std::ofstream output;
    output.open(filename);
    //check if this is ok
    if(!output.is_open())
        return false;
    output << *this;
    output.close();
    return true;
}

template<class T>
bool Matrix<T>::read_binary(std::string &filename)
{
    std::fstream input;
    input.open(filename);
    if(!input.is_open())
        return false;
    // std::vector<std::vector<T>> table;
    int height, width;

    input.read(reinterpret_cast<char *>(&height), sizeof(int));
    input.read(reinterpret_cast<char *>(&width), sizeof(int));

    table.resize(height, std::vector<T>(width));

    for(int i = 0; i < height; i++)
    {
        // std::cout << '\n';
        for(int j = 0; j < width; j++)
        {
            input.read(reinterpret_cast<char *>(&(table[i][j])), sizeof(T));
            // std::cout << table[i][j] << ' ';
        }
    }

    return true;
}

template<class T>
bool Matrix<T>::write_binary(std::string &filename)
{
    std::ofstream output;
    output.open(filename, std::ios::binary);
    if(!output.is_open())
        return false;

    auto sizes = get_dimensions();
    output.write(reinterpret_cast<const char *>(&(sizes.first)), sizeof(int));
    output.write(reinterpret_cast<const char *>(&(sizes.second)), sizeof(int));
    for(auto line : table)
    {
        for(T element : line)
        {
            output.write(reinterpret_cast<const char *>(&element), sizeof(T));
        }
    }
    output.close();
    return true;
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
Matrix<T> Matrix<T>::operator /(T second)const
{
    return this->*(1/second);
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
std::ostream &operator <<(std::ostream &out, const Matrix<T> &matrix1)
{
    for(auto line : matrix1.table)
    {
        for (auto element : line)
        {
            out << element << '\t';
        }
        out << '\n';
    }

    return out;
}

template<class T>
std::istream &operator >>(std::istream &in, Matrix<T> &matrix1)
{
    std::vector<std::vector<T>> new_table; //(height, std::vector<T>(width));
    std::string line;
    std::stringstream sstream;
    getline(in, line, '\n');
    int size = -1;
    while(line.size() > 0 || line == "\n")
    {
        std::replace(line.begin(), line.end(), '\t', ' ');
        std::replace(line.begin(), line.end(), ',', '.');
        new_table.push_back(std::vector<T>());
        sstream.str(line);
        T elem;
        while(sstream >> elem)
        {
            new_table.back().push_back(elem);
        }
        sstream.clear();
        getline(in, line, '\n');
        if(size == -1)
            size = new_table.back().size();
        else if(new_table.back().size() != size)
            throw std::invalid_argument("Different row sizes. Data is invalid!\n");
    }


    new (&matrix1) Matrix<T>(new_table);
    return in;
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
