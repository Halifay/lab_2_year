#include <iostream>
#include "matrix.cpp"
#include <fstream>

void test_Matrix()
{
    int side = 3, test_n = 1, subtest_n=0;
    Matrix<int> mat1(side, side);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << "\n" << mat1 << std::endl; // check (int, int) constructor

    std::vector<int> vector_tester = std::vector<int>{1, 2, 3};
    Matrix<int> vector(vector_tester);
    subtest_n++;
    std::cout << "test " << test_n << "." << subtest_n << '\n' << vector << std::endl;

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

void second_and_third_lab_tests()
{
    Matrix<double> first(3, 3, 1), second(3, 3, 2);
    std::cout << "first\n" << first << std::endl;
    std::cout << "second\n" << second << std::endl;
    std::cout << "rank of second matrix\n" << second.rank() << std::endl;
    std::cout << "det = " << second.Gauss() << std::endl;
    std::cout << "second matrix in gaussian form\n" << second << std::endl;
    std::cout << "previous matrix transposed\n" << first.Transpose() << std::endl;
    std::cout << "first matrix inverted\n" << first.Transpose().inverse() << std::endl;
    std::cout << "first matrix * first matrix inverted\n" << first * first.inverse() << std::endl;
    std::cout << "first matrix Frobenius norm\n" << first.m_form_frb() << std::endl;

    std::cout << "\nNext are vector operations" << std::endl;
    std::vector<double> first_vector = {1/std::sqrt(3), 1/std::sqrt(3), 1/std::sqrt(3)},
        second_vector = {1, 1, -1};
    Matrix<double> first_v(first_vector), second_v(second_vector);
    std::cout << "First vector: " << first_v << std::endl << "Second vector: " << second_v << std::endl;
    std::cout << "Scalar product: " << first_v.scalar(second_v) << std::endl;
    std::cout << "Euclidean norm of the first vector: " << first_v.v_norm_euc() << std::endl;
    std::cout << "Maximum norm of the second vector: " << second_v.v_norm_max() << std::endl;
    std::cout << "Radian angle between two vectors: " << first_v.angle(second_v) << "\nIn degrees: "
        << first_v.angle(second_v)/M_PI*180 << std::endl;
}

void fourth_lab_tests()
{
    Matrix<double> file_input;
    std::string common_path = "/home/mikhail/Garage/C++/lab2_1C++";
    std::string data = "/data.", loadings = "/loadings.", scores = "/scores.";
    std::cout <<"Reading data.txt" << std::endl;

    std::cout << "writing data.txt contents to data.bin" << std::endl;
    std::string input_file, text_output_file, binary_output_file;
    input_file = common_path + data + "txt";
    text_output_file = common_path + data + "text";
    binary_output_file = common_path + data + "bin";
    file_input.read_text(input_file);
    std::cout << file_input << std::endl;
    file_input.write_text(text_output_file);
    file_input.write_binary(binary_output_file);

    std::cout << "writing loadings.txt contents to loadings.bin" << std::endl;
    input_file = common_path + loadings + "txt";
    text_output_file = common_path + loadings + "text";
    binary_output_file = common_path + loadings + "bin";
    file_input.read_text(input_file);
    std::cout << file_input << std::endl;
    file_input.write_text(text_output_file);
    file_input.write_binary(binary_output_file);

    std::cout << "writing scores.txt contents to scores.bin" << std::endl;
    input_file = common_path + scores + "txt";
    text_output_file = common_path + scores + "text";
    binary_output_file = common_path + scores + "bin";
    file_input.read_binary(binary_output_file);
    // file_input.read_text(input_file);
    std::cout << file_input << std::endl;
    file_input.write_text(text_output_file);
    file_input.write_binary(binary_output_file);

    std::cout << "Check input yourself, type numbers separated by spaces in rows separated by line breaks."
                 "Don't forget to press enter twice at the end." << std::endl;
    Matrix<int> hand_input{};
    std::cin >> hand_input;
    std::string user_input = common_path + "/user_input.txt";
    hand_input.write_text(user_input);
    std::cout << "Your input is\n" << hand_input << std::endl;
    std::cout << "It saved under user_input.txt" << std::endl;
}

int main() {

    // first_lab_tests();
    // second_and_third_lab_tests();
    fourth_lab_tests();

    // Matrix<double> example(3, 2, 1);
    // std::cout << example << std::endl;
    // std::cout << example.Transpose() << std::endl;

    return 0;
}
