#include <iostream>
#include "matrix.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    int side = 3;
    std::vector<std::vector<int>> table = std::vector<std::vector<int>>(side, std::vector<int>(side, 1));
    matrix::DiagonalMatrix<int> imat(side, side);
    for(int i = 0; i < side; i++)
    {
        std::cout << std::endl;
        for(int j = 0; j < side; j++)
            std::cout << imat[i][j] << ' ';
    }
    return 0;
}
