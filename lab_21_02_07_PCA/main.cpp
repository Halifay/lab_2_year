#include <iostream>
#include "PCA.h"
#include "PCA.cpp"
// #include "matrix.cpp"

int main() {
    std::string common_path = "/home/mikhail/Garage/C++/lab_21_02_07_PCA";
    Matrix<long double> input;
    std::string path_to_data = common_path + "/data.txt";
    // std::string path_to_data = common_path +"/write.txt";
    input.read_text(path_to_data);
    std::cout << "input table\n" << input << std::endl;
    PCA algorithm(input);

    return 0;
}
