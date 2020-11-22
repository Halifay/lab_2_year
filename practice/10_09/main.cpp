#include <iostream>

class SquareMatrix
{
public:
    size_t side;
    int **table;
public:
    SquareMatrix(size_t side, int **contents):side(side)
    {
        table = (int **)malloc(side*sizeof(int *));
        for(int i = 0; i < side; i++)
        {
            table[i] = (int *)malloc(side*sizeof(int));
            for (int j = 0; j < side; j++)
                table[i][j] = contents[i][j];
        }
    }

    int *operator[](int i)const
    {
        return table[i];
    }

    SquareMatrix& operator +(SquareMatrix &right)
    {
        for(int i = 0; i < side; i++)
            for(int j = 0; j < side; j++)
                table[i][j] += right[i][j];
        return *this;
    }

    SquareMatrix& operator -(SquareMatrix &right)
    {
        for(int i = 0; i < side; i++)
            for(int j = 0; j < side; j++)
                table[i][j] -= right[i][j];
        return *this;
    }

    bool operator ==(SquareMatrix &right)const
    {
        if(side != right.side)
            return false;
        for(int i = 0; i < side; i++)
            for(int j = 0; j < side; j++)
                if (table[i][j] != right[i][j])
                    return false;
        return true;
    }

    friend std::ostream &operator <<(std::ostream &out, SquareMatrix const&matrix)
    {
        for(int i = 0; i < matrix.side; i++)
        {
            for(int j = 0; j < matrix.side; j++)
                out << matrix[i][j] << ' ';
            out << '\n';
        }
        return out;
    }

};

int main() {
    size_t side = 3;
    int **a = (int **)malloc(sizeof(int *) * side);
    for(int i = 0; i < side; i++)
    {
        a[i] = (int *)malloc(sizeof(int) *side);
        for(int j = 0; j < side; j++)
            a[i][j] = i+j;
    }
    SquareMatrix matrix(side, a);
    std::cout << matrix + matrix;
    return 0;
}
