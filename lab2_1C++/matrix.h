//
// Created by mikhail on 22.11.2020.
//

#ifndef LAB2_1C___MATRIX_H
#define LAB2_1C___MATRIX_H
#include <vector>
namespace matrix
{
    template<class T>
    class Matrix
    {
    protected:
        std::vector<std::vector<T>> table;
    public:
        Matrix(int, int);
        Matrix(std::vector<std::vector<T>> &);

        std::pair<int, int> get_dimensions();
        bool check_sizes(const Matrix<T> &, const Matrix<T> &);
        virtual void validate();

        // ALERT! User can change variable which he should not with [] operator!!!
        const std::vector<T> &operator[](int);
        Matrix<T> operator+(const Matrix<T>&);
        Matrix<T> operator-(const Matrix<T>&);
        Matrix<T> operator *(const Matrix<T>&);
        template<typename mult=int>
        Matrix<T> operator *(mult);
        Matrix<T> adamar(const Matrix<T>&);
        const Matrix<T> &operator =(const Matrix<T>&);

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
        LowerTriangleMatrix(std::vector<T>);
        void validate()override;
    };

    template<class T>
    class SymmetricalMatrix: public Matrix<T>
    {
    public:
        SymmetricalMatrix(int, T);
        SymmetricalMatrix(std::vector<T>);
        void validate()override;

    };
}

#endif //LAB2_1C___MATRIX_H
