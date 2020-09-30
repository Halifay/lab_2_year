#include <iostream>
#include <fstream>
#include "student.cpp"

void generate_list(char *filename, int r_seed = 0, int students_count = 100)
{
    std::ofstream my_file(filename);
    srand(r_seed);
    std::string names[] = {"Podshum", "Razbor", "Pribor", "Poliv", "Prikol", "Obval", "Ugon", "Rulon",
                           "Bouquet", "Pobeg", "Kamaz", "Record", "Razgon", "Zahvat", "Zalog", "Nalog"};
    std::string surnames[] = {"Priboev", "Zavalov", "Gazonov", "Zaboyev", "Harleev", "Oboev", "Pionov",
                              "Poletov", "Zlodeev", "Nadoev", "Piketov", "Pokoev", "Uspehov", "Sdohodov"};
    std::string faculty = "miem", specialization = "am";
    my_file << students_count << '\n';
    for(int i = 0; i < students_count; ++i)
    {
        std::string full_name = names[rand() % names->length()] + " " + surnames[rand() % surnames->length()];
        std::cout << full_name << std::endl;
        int points_sum = rand()%101;
        my_file << full_name << '\n';
        my_file << faculty << ' ' << specialization << ' ' << points_sum << '\n';
    }
}


void heap_sort(Student *student_list)
{

}


void selection_sort(Student *student_list)
{

}


void run_sorts(char *filename)
{
    //read students to list

    //copy list

    //run both sorts and measure time
}


int main()
{
    std::string name = "John Smith", faculty = "miem", spec = "am";
    Student first_student = Student(name, faculty, spec, 228);
    first_student.print_student();
    generate_list("~/Garage/C++/lab2C++/students1.txt");
    return 0;
}
