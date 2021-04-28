#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::mutex dice;
std::vector<int> map(101, 0);
int second_position = 0, first_position = 0;
bool game_ended = false, first_moves = true;

void first_move()
{
    while(!game_ended)
    {
        if(!first_moves)
            continue;
        std::lock_guard<std::mutex> move(dice);
        first_moves = false;
        int dropped = std::rand() % 6 + 1;
        first_position += dropped;
        first_position = (first_position - 1) % 100 + 1;
        first_position += map[first_position];
        first_position = (first_position + 99) % 100 + 1;
        if (first_position == 100) {
            std::cout << "First won!" << std::endl;
            game_ended = true;
            return;
        }
        std::cout << "First is now on " << first_position << std::endl;
    }
}

void second_move()
{
    while(!game_ended)
    {
        if (first_moves)
            continue;
        std::lock_guard<std::mutex> move(dice);
        first_moves = true;
        int dropped = std::rand() % 6 + 1;
        second_position += dropped;
        second_position = (second_position + 99) % 100 + 1;
        second_position += map[second_position];
        second_position = (second_position + 99) % 100 + 1;
        if (second_position == 100) {
            std::cout << "Second won!" << std::endl;
            game_ended = true;
            return;
        }
        std::cout << "Second is now on " << second_position << std::endl;
    }
}

int main() {
    srand(time(NULL));
    for(int i = 0; i < map.size(); i+=3)
    {
        map[i] += (rand()%7) - 3;
    }
    std::thread first_player(first_move), second_player(second_move);
    first_player.join();
    second_player.join();
    return 0;
}
