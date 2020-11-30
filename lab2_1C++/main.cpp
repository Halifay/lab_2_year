#include <iostream>
#include "matrix.cpp"

void test_Matrix()
{
    int side = 3;
    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side, 1));
    matrix::SymmetricMatrix<int> imat(side, side);
    Matrix<int> mat = (imat)+(imat);
    std::cout << mat;
}

void test_IdentityMatrix()
{

}

void test_DiagonalMatrix()
{

}

void test_UpperTriangleMatrix()
{

}

void test_LowerTriangleMatrix()
{

}

void test_SymmetricMatrix()
{

}


int main() {
    std::cout << "Hello, World!" << std::endl;
    test_Matrix();
    test_IdentityMatrix();
    test_DiagonalMatrix();
    test_UpperTriangleMatrix();
    test_LowerTriangleMatrix();
    test_SymmetricMatrix();

    return 0;
}
