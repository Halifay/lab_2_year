#include <iostream>
#include "matrix.cpp"

void test_Matrix()
{
    int side = 3, test_n = 1, subtest_n=0;
    Matrix<int> mat1(side, side);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, int) constructor

    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side));
    for(int i = 0; i < side; i++)
        for(int j =0; j < side; j++)
        {
            table[i][j] = 10*i + j;
        }
    Matrix<int> mat2(table);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2 << std::endl; // check vector constructor

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator


    std::vector<std::vector<int>> vertical_table = std::vector<std::vector<int>>(side, std::vector<int>(side*2));
    std::vector<std::vector<int>> horizontal_table = std::vector<std::vector<int>>(side*2, std::vector<int>(side));
    for(int i = 0; i < side; i++)
        for(int j = 0; j < side*2; j++)
        {
            vertical_table[i][j] = i+j;
            horizontal_table[j][i] = i+j;
        }
    Matrix<int> vmat5(vertical_table), hmat5(horizontal_table);
    Matrix<int> mat51 = (hmat5) * (vmat5);
    Matrix<int> mat52 = (vmat5) * (hmat5);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat51 << mat52 << std::endl; //check * for two matrix operator

    Matrix<int> mat61 = 10 * mat4, mat62 = mat4 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat4.hadamard(mat4);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product
}

void test_IdentityMatrix()
{
    int side = 3, test_n = 2, subtest_n=0;
    IdentityMatrix<int> mat2(3);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2;

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n"  << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator

    Matrix<int> mat61 = 10 * mat4, mat62 = mat4 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat4.hadamard(mat4);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product

}

void test_DiagonalMatrix()
{
    int side = 3, value = 2, test_n = 3, subtest_n=0;
    DiagonalMatrix<int> mat1(side, value);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, T) constructor

    std::vector<int> table = std::vector<int>(side);
    for(int i = 0; i < side; i++)
            table[i] = i;
    DiagonalMatrix<int> mat2(table);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2 << std::endl; // check vector constructor

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator


    Matrix<int> mat5 = mat2 * mat2;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat5 << std::endl; //check * for two matrix operator

    Matrix<int> mat61 = 10 * mat2, mat62 = mat2 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat2.hadamard(mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product
}

void test_UpperTriangleMatrix()
{
    int side = 3, value = 2, test_n = 4, subtest_n=0;
    UpperTriangleMatrix<int> mat1(side, value);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, int) constructor

    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side));
    for(int i = 0; i < side; i++)
        for(int j =0; j < side; j++)
        {
            table[i][j] = 10*i + j;
        }
    UpperTriangleMatrix<int> mat2(table);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2 << std::endl; // check vector constructor

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator

    Matrix<int> mat5 = mat2*mat2;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat5 << std::endl; //check * for two matrix operator

    Matrix<int> mat61 = 10 * mat2, mat62 = mat2 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat2.hadamard(mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product
}

void test_LowerTriangleMatrix()
{
    int side = 3, value = 2, test_n = 5, subtest_n=0;
    LowerTriangleMatrix<int> mat1(side, value);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, int) constructor

    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side));
    for(int i = 0; i < side; i++)
        for(int j =0; j < side; j++)
        {
            table[i][j] = 10*i + j;
        }
    LowerTriangleMatrix<int> mat2(table);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2 << std::endl; // check vector constructor

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator

    Matrix<int> mat5 = mat2*mat2;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat5 << std::endl; //check * for two matrix operator

    Matrix<int> mat61 = 10 * mat2, mat62 = mat2 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat2.hadamard(mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product
}

void test_SymmetricMatrix()
{
    int side = 3, value = 2, test_n = 6, subtest_n=0;
    SymmetricMatrix<int> mat1(side, value);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, int) constructor

    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side));
    for(int i = 0; i < side; i++)
        for(int j =0; j < side; j++)
        {
            table[i][j] = 10*i + j;
        }
    SymmetricMatrix<int> mat2(table);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat2 << std::endl; // check vector constructor

    Matrix<int> mat3 = (mat2) + (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat3 << std::endl; // check + operator

    Matrix<int> mat4 = (mat3) - (mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat4 << std::endl; // check - operator

    Matrix<int> mat5 = mat2*mat2;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat5 << std::endl; //check * for two matrix operator

    Matrix<int> mat61 = 10 * mat2, mat62 = mat2 * 10;
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat61 << mat62 << std::endl; // check * operator for matrix and number

    Matrix<int> mat7 = mat2.hadamard(mat2);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat7 << std::endl; //check Hadamard product
}


void first_lab_tests()
{
    test_Matrix();
    test_IdentityMatrix();
    test_DiagonalMatrix();
    test_UpperTriangleMatrix();
    test_LowerTriangleMatrix();
    test_SymmetricMatrix();
}

void second_lab_tests()
{
    Matrix<double> first(3, 3, 1), second(3, 3, 2);
    std::cout << "first\n" << first << '\n';
    std::cout << "second\n" << second << '\n';
    std::cout << "det = " << first.Gauss() << '\n';
    std::cout << "first matrix in gaussian form\n" << first << '\n';
}

void third_lab_tests()
{

}

void fourth_lab_tests()
{

}

int main() {
    // first_lab_tests();
    second_lab_tests();
    third_lab_tests();
    fourth_lab_tests();

    return 0;
}
