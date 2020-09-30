#define _CRT_SECURE_NO_WARNINGS
#include "histogram.h"
#include <iostream>
#include <string.h>
#include <iomanip>
#include <algorithm>

using namespace std;

///////////////////////////////////////////////////////////////////
// ��������������� �������
void AddBar(Histogram &histogram, const char *strName);
bool AppendBar(Histogram &histogram, const char *strName);

///////////////////////////////////////////////////////////////////
// ���������� ������� �� ����� histogram.h


//-----------------------------------------------------------------
// ������� AddBlock ����������� �������� ������� strName ���������� histogram �� 1.
// ���� ������� � ����� ������ �� ����������, �� ���������.
void AddBlock(Histogram &histogram, const char *strName){
	if(!AppendBar(histogram, strName)){
		AddBar(histogram, strName);
	}
}


///////////////////////////////////////////////////////////////////
// ���������� ��������������� �������

//-----------------------------------------------------------------
// ������� AppendBar ����������� �������� ������� strName ���������� histogram �� 1.
bool AppendBar(Histogram &histogram, const char *strName){
	for(int i=0; i<histogram.nBarsSize; i++){
		if(strcmp(histogram.BarNames[i], strName)==0){
			histogram.nMaxBar = max(histogram.nMaxBar, ++histogram.Bars[i]);
			return true;
		}
	}
	return false;
}

// ������� AddBar ������� � ���������� histogram ����� ������� � ������ strName.
//-----------------------------------------------------------------
void AddBar(Histogram &histogram, const char *strName){
	char **newNames = new char *[histogram.nBarsSize+1];
	int   *newBars  = new int[histogram.nBarsSize+1];
	if(histogram.nBarsSize > 0){
		for(int i=0; i<histogram.nBarsSize; i++){
			newNames[i] = histogram.BarNames[i];
			newBars[i] = histogram.Bars[i];
		}
		delete[] histogram.BarNames;
		delete[] histogram.Bars;
	}

	newNames[histogram.nBarsSize] = new char[strlen(strName)+1];
	strcpy(newNames[histogram.nBarsSize], strName);
	newBars[histogram.nBarsSize] = 1;

	histogram.nBarsSize++;
	histogram.BarNames = newNames;
	histogram.Bars = newBars;
}


//SortByVal function for homework
void SortByVal(Histogram &histogram, bool b_ascending = true)
{
    pair<int, int>* sorting_pairs = (pair<int, int> *)malloc(histogram.nBarsSize * sizeof(pair<int, int>));
    for(int i = 0; i < histogram.nBarsSize; i++)
    {
        sorting_pairs[i] = {histogram.Bars[i], i};
    }
    if(b_ascending)
        std::sort(sorting_pairs, sorting_pairs+histogram.nBarsSize);
    else
        std::sort(sorting_pairs, sorting_pairs+histogram.nBarsSize, std::greater<pair<int, int> >());
    char **new_names = (char **)malloc(histogram.nBarsSize * sizeof(char *));
    for(int i = 0; i < histogram.nBarsSize; i++)
    {
        new_names[i] = histogram.BarNames[sorting_pairs[i].second];
        histogram.Bars[i] = sorting_pairs[i].first;
    }
    free(histogram.BarNames);
    free(sorting_pairs);
    histogram.BarNames = new_names;
}

//-----------------------------------------------------------------
// ������� PrintHistogram ������� ���������� �� �����.
void PrintHistogram(const Histogram &histogram){
    int max_length = 0;
    for(int i=0; i<histogram.nBarsSize; i++){
        int cur_len = strlen(histogram.BarNames[i]);
        if(max_length < cur_len)
            max_length = cur_len;
    }
    for(int i=0; i<histogram.nBarsSize; i++){
        printf("%-*s", max_length, histogram.BarNames[i]);
        cout << '|';
        cout << setfill(histogram.chBlock) << setw(10*histogram.Bars[i]/histogram.nMaxBar) << "" <<  endl;
    }
}
