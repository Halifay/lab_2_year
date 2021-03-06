//
// Created by mikhail on 30.09.2020.
//

#include <iostream>
#include <string>

class Student
{
public:
    std::string full_name, faculty, speciality;
    int point_sum;

    // Три конструктора для вызова без аргументов, с массивами символов и строками.
    Student()
    {
        full_name = "";
        faculty = "";
        speciality = "";
        point_sum = 0;
    }

    Student(std::string &full_name_s, std::string &faculty_s,
            std::string &speciality_s, int point_sum_s)
    {
        full_name = full_name_s;
        faculty = faculty_s;
        speciality = speciality_s;
        point_sum = point_sum_s;
    }

    Student(char *full_name_c, char *faculty_c,
            char *speciality_c, int point_sum_c)
    {
        full_name = std::string(full_name_c);
        faculty = std::string(faculty_c);
        speciality = std::string(speciality_c);
        point_sum = point_sum_c;
    }

    // Вроде ничего явно чистить не нужно
    ~Student()
    {
    }

    void print_student()
    {
        std::cout << full_name << " from " << faculty << " " <<
        speciality << " have sum of points of " << point_sum << std::endl;
    }

    // Всякие операторы
    Student &operator =(const Student &second)
    {
        if(this != &second) {
            full_name = second.full_name;
            faculty = second.faculty;
            speciality = second.speciality;
            point_sum = second.point_sum;
        }
        return *this;
    }

    bool operator ==(const Student &second)
    {
        bool result = true;
        result &= (full_name==second.full_name);
        result &= (faculty==second.faculty);
        result &= (speciality==second.speciality);
        result &= (point_sum==second.point_sum);
        return result;
    }

    bool operator !=(const Student &second)
    {
        return not (*this == second);
    }

    bool operator <(const Student &second)
    {
        return point_sum < second.point_sum || (point_sum == second.point_sum && full_name > second.full_name);
    }

    bool operator >(const Student &second)
    {
        return point_sum > second.point_sum || (point_sum == second.point_sum && full_name < second.full_name);
    }

    bool operator <=(const Student &second)
    {
        return !(*this > second);
    }

    bool operator >=(const Student &second)
    {
        return !(*this < second);
    }
};
