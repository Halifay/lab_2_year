
//-----------------------------------------------------------------
// ������� InitHistogram �������������� ������ �����������
void inline InitHistogram(Histogram &historgam){
	historgam.nBarsSize = 0;
	historgam.BarNames = 0;//������ ��������� �������������������� ���������
	historgam.Bars = 0;    //������ ��������� �������������������� ���������
	historgam.chBlock = '#';
	historgam.nMaxBar = 1;
}

//-----------------------------------------------------------------
// ������� DestroyHistogram ����������� ������� ������
void inline DestroyHistogram(Histogram &historgam){
	if(historgam.nBarsSize){
		delete[] historgam.BarNames;
		historgam.BarNames = 0; //������ ��������� ��������� ����� ������������ ������
		delete[] historgam.Bars;
		historgam.Bars = 0; //������ ��������� ��������� ����� ������������ ������
	}
	historgam.nMaxBar = 1;

}

#include "histogram.cpp"