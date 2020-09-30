//
// Created by mikhail on 30.09.2020.
//

#include "student.h"
#include <iostream>
#include <string>

class Student
{
public:
    std::string full_name, faculty, speciality;
    int point_sum;

    Student()
    {
        full_name = "";
        faculty = "";
        speciality = "";
        point_sum = 0;
    }

    Student(std::string &full_name_c, std::string &faculty_c,
            std::string &speciality_c, int point_sum_c)
    {
        // Student();
        full_name = full_name_c;
        faculty = faculty_c;
        speciality = speciality_c;
        point_sum = point_sum_c;
    }

    void print_student()
    {
        std::cout << full_name << " from " << faculty << " " <<
        speciality << " have sum of points of " << point_sum << std::endl;
    }

    bool operator<(const Student &second)
    {
        return point_sum<second.point_sum;
    }

    bool operator>(const Student &second)
    {
        return point_sum>second.point_sum;
    }

    bool operator<=(const Student &second)
    {
        return point_sum<=second.point_sum;
    }

    bool operator>=(const Student &second)
    {
        return point_sum>=second.point_sum;
    }
};
