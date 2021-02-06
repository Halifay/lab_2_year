#include <iostream>
#include <thread>
#include <vector>

std::vector<std::vector<int>> matrix({{1, 2, 3, 4, 5},{6, 7, 8, 9, 10},{-1, -2, -3, -4, -5},
                                        {-10, -9, -8, -7, -6},{1, 1, 1, 1, 1}});
int count;

void row_count(int i)
{
    int row = 0;
    for(int j : matrix[i])
        row += j;
    count += row;
}


int main() {
    std::thread row_counter_one(row_count, 0);
    std::thread row_counter_two(row_count, 1);
    std::thread row_counter_three(row_count, 2);
    std::thread row_counter_four(row_count, 3);
    std::thread row_counter_five(row_count, 4);

    row_counter_one.join();
    row_counter_two.join();
    row_counter_three.join();
    row_counter_four.join();
    row_counter_five.join();
    std::cout << count << std::endl;
    return 0;
}
