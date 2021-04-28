#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <sstream>

std::once_flag cleaned;
std::timed_mutex tmutex;
const int response_time = 1000;

void check_student(std::string name)
{
    using milliseconds = std::chrono::milliseconds;
    std::ostringstream current_stream;
    std::call_once(cleaned, [name](){std::cout << (name + " wiped the board.") << std::endl;});

    if(tmutex.try_lock_for(milliseconds(response_time)))
    {
        current_stream << name << " is present.\n";
        std::this_thread::sleep_for(milliseconds(response_time/6));
        tmutex.unlock();
    }
    else
        current_stream << name << " is absent.\n";
    std::cout << current_stream.str();
}

int main()
{
    std::vector<std::string> names = {"Alice", "Bob", "Clare", "David", "Eva", "Fred", "Gregor", "Hana"};
    std::vector<std::thread> threads;
    for(std::string name : names)
        threads.push_back(std::thread(check_student, name));
    for(auto& process : threads)
        process.join();
    return 0;
}
