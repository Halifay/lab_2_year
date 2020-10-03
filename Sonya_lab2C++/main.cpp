#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <limits>
#include <unistd.h>
#include <climits>
#include <time.h>
#include <stdlib.h>
// #include <windows.h>

using namespace std;
const int step = 300;

class Company {
public:
    string FIO, O_name, number, email;

    Company(string &FIO, string &O_name, string &number, string &email){
        this->FIO = FIO;
        this->O_name = O_name;
        this->number = number;
        this->email = email;
    }

    Company &operator=(const Company &left){
        if(this != &left) {
            FIO = left.FIO;
            O_name = left.O_name;
            number = left.number;
            email = left.email;
        }
        return *this;
    }

    bool operator<(const Company &right)const{
        return FIO < right.FIO || (FIO == right.FIO && O_name < right.O_name);
    }

    bool operator>(const Company &right)const{
        return FIO > right.FIO || (FIO == right.FIO && O_name > right.O_name);
    }

    bool operator<=(const Company &right)const{
        return !(*this > right);
    }

    bool operator>=(const Company &right)const{
        return !(*this < right);
    }
};

void generate_data(string &filename, int size){
    ofstream myfile;
    myfile.open(filename);
    if (not myfile.is_open()){
        cout << "Файл не открывается для записи!!! "  << filename << "\n";
        return;
    }
    myfile << size << '\n';
    for(int i = 0; i < size; i++){
        myfile << rand() << ' ' << rand() << ' ' << rand() << '\n'; // ФИО
        myfile << rand() << '\n'; // название компании
        myfile << rand() << ' ' << rand() << '\n'; // телефон и email
    }
    myfile.close();
}

void read_data(vector<Company> &companies, string &filename){
    fstream myfile;
    myfile.open(filename);
    if (not myfile.is_open()){
        cout << "Файл не открывается для чтения!!!\n";
        return;
    }
    int size;
    myfile >> size;
    string FIO, O_name, number, email;
    getline( myfile, FIO);
    for(int i = 0; i < size; i++){
        getline(myfile, FIO);
        getline(myfile, O_name);
        myfile >> number >> email;
        companies.emplace_back(Company(FIO, O_name, number, email));
        getline(myfile, FIO);
    }
    myfile.close();
}

bool is_ascending(vector<Company> &companies){
    for(int i = 1; i < companies.size(); i++){
        if(companies[i-1] > companies[i])
            return false;
    }
    return true;
}


bool choose(Company first, Company second, bool a) {
    if (a && (first < second) > 1) { //выбираем название организации
        return true;
    }
    else if (!a && (first < second) % 2) { //выбираем название ФИО, %2 отрезает все до первого бита
        return true;
    }
    else { //first >= second
        return false;
    }
}


void qsortRecursive(vector<Company> &arr, unsigned int n, bool a) {

    //Указатели в начало и в конец массива
    int i = 0;
    int j = n - 1;

    //Центральный элемент массива
    Company mid = arr[n / 2];


    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (choose(arr[i], mid, a)) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (choose(mid, arr[j], a)) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            Company tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsortRecursive(arr, j + 1, a);
    }
    if (i < n) {
        //"Првый кусок"
        qsortRecursive(arr, n-i, a);
    }
}

int company_comparator (const void *left, const void *right){
    Company left_c = *((Company *)left), right_c = *((Company *)right);
    if(left_c < right_c) return -1;
    if(left_c > right_c) return 1;
    return 0;
}

void quick_sort(vector<Company> &companies){
    Company *array = (Company *)calloc(companies.size(), sizeof(Company));
    for(int i = 0; i < companies.size(); i++){
        array[i] = companies[i];
    }
    qsort(array, companies.size(), sizeof(Company), company_comparator);
    companies = vector<Company>(array, array+companies.size());
    free(array);
}

void shaker_sort(vector<Company> &companies){
    int i, j, k;
    int last = companies.size();
    for(i = 0; i < last;) {
        for(j = i+1; j < last; j++) {
            if(companies[j] < companies[j-1])
                swap(companies[j], companies[j-1]);
        }
        last--;
        for(k = last-1; k > i; k--) {
            if(companies[k] < companies[k-1])
                swap(companies[k], companies[k-1]);
        }
        i++;
    }
}

string get_current_directory(){
    // on linux
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return string( result, (count > 0) ? count : 0 );

    // on windows
    // char result[ MAX_PATH ];
    // return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}


int main() {
    for(int i = 1; i < 11; i++){
        cout << "Start of " << i << " test" << endl;
        string data_path = get_current_directory() + "data" + string(to_string(i)) + ".txt";
        generate_data(data_path, i*step);

        vector<Company> companies1, companies2;
        read_data(companies1, data_path);
        read_data(companies2, data_path);
        clock_t start, end;
        start = clock();
        quick_sort(companies1);
        if (!is_ascending(companies1))
            cout << "Быстрая сортировка сломалась на тесте " + data_path << '\n';
        end = clock();
        cout << "Быстрая сортировка для " << i*step << " элементов отработала за " << (((double)(end - start))/CLOCKS_PER_SEC) << "секунд\n";

        start = clock();
        shaker_sort(companies2);
        if (!is_ascending(companies2))
            cout << "Шейкер-сортировка сломалась на тесте " + data_path << '\n';
        end = clock();
        cout << "Шейкер-сортировка для " << i*step << " элементов отработала за " << (((double)(end - start))/CLOCKS_PER_SEC) << "секунд\n";
        cout << '\n';
    }



//     bool a;
//     vector<Company> n;
//     ofstream fin1;
//     fin1.open("laba2.txt");
//
//    for (int i = 0; i < 10; ++i) {
//        for (int r = 0; r < 3; r++) {
//            int y = rand() % 10 + 1;
//            for (int j = 0; j < y; y++) {
//                fin1 << char(rand() % 26 + 0x61);
//            }
//        }
//
//     }
//
//
//
//     ifstream fin("laba2.txt");
//
//     for (int i = 0; i < 3; ++i) {
//         Company z;
//         string a,b,c;
//         fin >> a >> b >> c;
//         z.FIO = a + " " + b + " " + c;
//         fin >> z.O_name >> z.number >> z.email;
//         n.push_back(z);
//     }
//
//     cout << "Choose what to sort: 0 - Name and Surname, 1 - Name of Company" << endl;
//     cin >> a;
//     qsortRecursive(n,n.size(),a);
//
//     for (int i = 0; i < 3; ++i) {
//         cout << n[i].FIO << endl << n[i].O_name << endl << n[i].number << endl << n[i].email << endl << endl;
//     }
//
 }
