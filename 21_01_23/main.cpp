#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

const int rows = 7, columns = 5;
std::vector<std::vector<int>> matrix(rows);
std::mutex mutex;
int count = 0;

void counter(int row, int cols, int number)
{
    for(int i = 0; i < cols; i++)
    {
        if(matrix[row][i] == number)
        {
            std::lock_guard<std::mutex> guardian_angel(mutex);
            count++;
        }
    }
}

int main() {
    for(int i = 0; i < rows; i++)
    {
        matrix[i].resize(columns);
        for(int j = 0; j < columns; j++)
        {
            matrix[i][j] = (i + j) % 3 + 1;
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::thread> threads(rows);
    for(int i = 0; i < rows; i++)
    {
        threads[i] = std::thread(counter, i, columns, 1);
    }

    for(int i = 0; i < rows; i++)
    {
        threads[i].join();
    }

    std::cout << "Number of ones is " << count << std::endl;

    return 0;
}
