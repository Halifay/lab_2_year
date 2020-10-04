#include <iostream>
#include <fstream>
#include "student.cpp"
#include <unistd.h>
#include <chrono>

const int max_full_name_size = 256;

// Функция для генерации списков учащихся
void generate_list(std::string &filename, int r_seed = 0, int students_count = 100)
{
    std::ofstream my_file;
    my_file.open(filename);
    if(not my_file.is_open())
    {
        std::cout << "Not open!!!\n";
        return;
    }
    std::cout << filename << std::endl;
    srand(r_seed);
    std::string names[] = {"Podshum", "Razbor", "Pribor", "Poliv", "Prikol", "Obval", "Ugon", "Rulon",
                           "Bouquet", "Pobeg", "Kamaz", "Record", "Razgon", "Zahvat", "Zalog", "Nalog",
                           "Pogrom"};
    std::string surnames[] = {"Priboev", "Zavalov", "Gazonov", "Zaboyev", "Harleev", "Oboev", "Pionov",
                              "Poletov", "Zlodeev", "Nadoev", "Piketov", "Pokoev", "Uspehov", "Sdohodov",
                              "Cowboyev"};
    std::string faculty = "miem", specialization = "am";
    my_file << students_count << '\n';
    for(int i = 0; i < students_count; ++i)
    {
        std::string full_name = names[rand() % names->length()] + " " + surnames[rand() % surnames->length()];
        // std::cout << full_name << std::endl;
        int points_sum = rand()%101;
        my_file << full_name << '\n';
        my_file << faculty << ' ' << specialization << ' ' << points_sum << '\n';
    }
    my_file.close();
}


// Алгоритм сортировки кучей
// Оба алгоритма сортировки принимают на вход массив студентов и размер этого массива
// Сортируют студентов в убывающем порядке по количеству баллов и в алфавитном по ФИО
void heap_sort(Student *student_list, int list_size)
{
    Student *student_heap = (Student *)calloc(sizeof(Student), list_size);
    // int max_int = (int)(((unsigned int)-1)>>1);
    int min_sum = -1;
    Student null_student((char *)"", (char *)"", (char *)"", min_sum);
    for(int i = 0; i < list_size; i++)
    {
        student_heap[i] = student_list[i];
        int cur_pos = i;
        while(cur_pos > 0 && student_heap[cur_pos] > student_heap[(cur_pos-1)/2])
        {
            std::swap(student_heap[cur_pos], student_heap[(cur_pos-1)/2]);
            cur_pos = (cur_pos - 1)/2;
        }
    }

    for(int i = 0; i < list_size; i++)
    {
        student_list[i] = student_heap[0];
        student_heap[0] = null_student;
        int cur_pos = 0;
        while(cur_pos*2 + 2 <= list_size)
        {
            if(cur_pos*2+2 == list_size)
            {
                std::swap(student_heap[cur_pos*2+1], student_heap[cur_pos]);
                break;
            }
            if(student_heap[cur_pos*2+1] == null_student && student_heap[cur_pos*2+2] == null_student)
                break;
            if(student_heap[cur_pos*2+1] > student_heap[cur_pos*2+2])
            {
                std::swap(student_heap[cur_pos], student_heap[cur_pos*2+1]);
                cur_pos = cur_pos*2+1;
            }
            else
            {
                std::swap(student_heap[cur_pos], student_heap[cur_pos * 2 + 2]);
                cur_pos = cur_pos*2+2;
            }
        }
    }
    free(student_heap);
}


// Алгоритм сортировки выбором
void selection_sort(Student *student_list, int list_size)
{
    for(int i = 0; i < list_size; i++)
    {
        int maximal_element = i;
        for(int j = i+1; j < list_size; j++)
        {
            if(student_list[j] > student_list[maximal_element])
                maximal_element = j;
        }
        std::swap(student_list[i], student_list[maximal_element]);
    }
}


// Функция для чтения данных студентов из указанного текстового файла
// Принимает на вход ссылку на массив, который нужно заполнить, путь до файла и число количества записей в файле
void read_students_data(Student *&students_list, std::string &filename, int &student_number)
{
    std::fstream my_file;
    my_file.open(filename);
    my_file >> student_number;
    students_list = (Student *)malloc(student_number * sizeof(Student));

    for(int i = 0; i < student_number; i++)
    {
        char *c_full_name = (char *)calloc(max_full_name_size, sizeof(char));
        std::string trash;
        std::string full_name, faculty, specialization;
        int score;
        std::getline(my_file, trash);
        my_file.getline(c_full_name, max_full_name_size);
        full_name = std::string(c_full_name);
        my_file >> faculty >> specialization >> score;
        students_list[i] = Student(full_name, faculty, specialization, score);
    }
    my_file.close();
}


// Проверяет, что элементы массива расположены в убывающем порядке
bool is_descending(Student *&student_list, int student_count)
{
    for(int i = 1; i < student_count; i++)
    {
        if(student_list[i-1] < student_list[i])
            return false;
    }
    return true;
}


// Читает данные, запускает обе сортировки и засекает время их работы
void run_sorts(std::string &filename)
{
    //read list from file
    Student *first_students_list, *second_students_list;
    int student_number;
    read_students_data(first_students_list, filename, student_number);
    if(is_descending(first_students_list, student_number))
    {
        std::cout << "Input list " << filename << " is already sorted!!!" << std::endl;
    }

    //copy list
    read_students_data(second_students_list, filename, student_number);

    //run both sorts and measure time
    auto first_start = std::chrono::high_resolution_clock::now();
    heap_sort(first_students_list, student_number);
    if(!is_descending(first_students_list, student_number))
    {
        std::cout << "Heap sort is broken on test " << filename << std::endl;
    }
    auto first_stop = std::chrono::high_resolution_clock::now();
    std::cout << "Heap sort worked for " << std::chrono::duration_cast<std::chrono::
    microseconds>(first_stop - first_start).count()/(1.0e6) << " seconds" << std::endl;

    auto second_start = std::chrono::high_resolution_clock::now();
    selection_sort(second_students_list, student_number);
    if(!is_descending(second_students_list, student_number))
    {
        std::cout << "Selection sort is broken on test " << filename << std::endl;
    }
    auto second_stop= std::chrono::high_resolution_clock::now();
    std::cout << "Selection sort worked for " << std::chrono::duration_cast<std::chrono::
    microseconds>(second_stop - second_start).count()/(1.0e6) << " seconds" << std::endl;

    //free arrays
    free(first_students_list);
    free(second_students_list);
}


int main()
{
    std::string path_to_file = "/home/mikhail/Garage/С++/lab2C++/students";
    std::string end_filename = "0.txt";
    int entries_num = 500, step = 500;
    for(int i = 0; i < 7; i++)
    {
        std::cout << "Experiment number " << i+1 << " with " << entries_num << " entries\n";
        std::string full_filename = path_to_file + end_filename;
        generate_list(full_filename, i, entries_num);
        run_sorts(full_filename);
        std::cout << std::endl;
        ++end_filename[0];
        entries_num += step;
    }
    return 0;
}
