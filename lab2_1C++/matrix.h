//
// Created by mikhail on 22.11.2020.
//

#ifndef LAB2_1C___MATRIX_H
#define LAB2_1C___MATRIX_H
#include <vector>
#include <iostream>

namespace matrix{
    template<class T>
    class Matrix;
}

template<class T>
std::ostream &operator<<(std::ostream&, const matrix::Matrix<T>&);
template<class T>
std::istream &operator>>(std::istream&, const matrix::Matrix<T>&);

namespace matrix
{
    template<class T>
    class Matrix
    {
    protected:
        std::vector<std::vector<T>> table;
    public:
        Matrix(int, int);
        Matrix(int, int, int, int max = 10);
        Matrix(std::vector<std::vector<T>> &);
        Matrix(std::vector<T> &);

        std::pair<int, int> get_dimensions()const;
        bool check_sizes(const Matrix<T> &, const Matrix<T> &)const;
        virtual void validate();
        T Gauss(int from_up = 0, int from_left = 0);
        T determinant();
        T scalar(Matrix<T> &);
        T v_norm_max();
        T v_norm_euc();
        double angle(Matrix &);
        int rank();
        Matrix<T> inverse();
        Matrix<T> &Transpose();


        // ALERT! User can change variable and implicitly change type of matrix (without logicaly changing it) with [] operator!!!
        const std::vector<T> &operator[](int)const;
        std::vector<T> &operator[](int);
        Matrix<T> operator+(const Matrix<T> &)const;
        Matrix<T> operator-(const Matrix<T> &)const;
        Matrix<T> operator*(const Matrix<T> &)const;
        Matrix<T> operator*(T)const;
        Matrix<T> hadamard(const Matrix<T> &)const;
        Matrix<T> &operator=(const Matrix<T> &);


        template<class T2>
        friend std::ostream &::operator<<(std::ostream &, const matrix::Matrix<T2> &);
        template<class T2>
        friend std::istream &::operator>>(std::istream &, const matrix::Matrix<T2> &);
    };

    template<class T>
    class IdentityMatrix: public Matrix<T>
    {
    public:
        IdentityMatrix(int);
        void validate()override;
    };

    template<class T>
    class DiagonalMatrix: public Matrix<T>
    {
    public:
        DiagonalMatrix(int, T);
        DiagonalMatrix(std::vector<T>);
        void validate()override;
    };

    template<class T>
    class UpperTriangleMatrix: public Matrix<T>
    {
    public:
        UpperTriangleMatrix(int, T);
        UpperTriangleMatrix(std::vector<std::vector<T>>);
        void validate()override;
    };

    template<class T>
    class LowerTriangleMatrix: public Matrix<T>
    {
    public:
        LowerTriangleMatrix(int, T);
        LowerTriangleMatrix(std::vector<std::vector<T>>);
        void validate()override;
    };

    template<class T>
    class SymmetricMatrix: public Matrix<T>
    {
    public:
        SymmetricMatrix(int, T);
        SymmetricMatrix(std::vector<std::vector<T>>, bool upper=true);
        void validate()override;

    };
}

#endif //LAB2_1C___MATRIX_H
