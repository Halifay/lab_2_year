#include "histogram.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>


int main(){
    const char * const strProgramName = "Histogrammer 2.0 NeW_AgE";

    std::cout << std::setfill('*') << std::setw(strlen(strProgramName)+4) << "" << std::endl;
    std::cout << '*' << std::setfill(' ') << std::setw(strlen(strProgramName)+3) << '*' << std::endl;
    std::cout << "* " << strProgramName << " *" << std::endl;
    std::cout << '*' << std::setfill(' ') << std::setw(strlen(strProgramName)+3) << '*' << std::endl;
    std::cout << std::setfill('*') << std::setw(strlen(strProgramName)+4) << "" << std::endl << std::endl;

    Histogram myBarChart;

    InitHistogram(myBarChart);
    std::string input_string;
    std::string delimiter = " ";
    getline(cin, input_string);
    int end_pos = 0;
    std::string current_word;
    while((end_pos = input_string.find(delimiter)) != std::string::npos)
    {
        current_word = input_string.substr(0, end_pos);
        if(current_word.length() > 0)
            AddBlock(myBarChart, to_string(current_word.length()).c_str());
        input_string.erase(0, end_pos + delimiter.length());
    }
    if(input_string.length() > 0)
        AddBlock(myBarChart, to_string(input_string.length()).c_str());

    printf("Input order\n");
    PrintHistogram(myBarChart);
    printf("\nAscending order\n");
    SortByVal(myBarChart);
    PrintHistogram(myBarChart);
    printf("\nDescending order\n");
    SortByVal(myBarChart, false);
    PrintHistogram(myBarChart);
    printf("\n");
    DestroyHistogram(myBarChart);

    return 0;
}
