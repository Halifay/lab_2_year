#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::vector<std::string>& file_reader(std::vector<std::string>& names, std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    if(file.is_open())
    {
        while(getline(file, line))
        {
            std::string name, surname, family_name;
            std::istringstream input_line(line);
            input_line >> name >> surname >> family_name;
            std::string one_name = "N:" + name + ";P:" + family_name + ";S:" + surname;
            names.push_back(one_name);
        }
    } else std::cout << "File " << filename << " didn't open" << std::endl;
    return names;
}

int main() {
    std::vector<std::string> names;
    // Здесь должен быть ваш путь до файла,
    std::string filename = "/home/mikhail/Garage/C++/03.11.20/names.txt";
    file_reader(names, filename);
    for(std::string full_name :names)
        std::cout << full_name << std::endl;
    return 0;
}
