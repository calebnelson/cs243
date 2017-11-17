#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "TimeManagerWindows.h"
using namespace std;

void TimeManager::start(){
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&st);
}

void TimeManager::end(){
	QueryPerformanceCounter(&ed);
	interval = (double) (ed.QuadPart - st.QuadPart) / frequency.QuadPart;
}

double TimeManager::getInterval(){
	return interval;
}

//for testing
/*int main(){
	TimeManager tm = TimeManager();
	tm.start();
	cin.ignore();
	tm.end();
	cout << "Time Elapsed: " << tm.getInterval();
}*/
