/*
 * CSVManager.cc
 *
 *  Created on: Nov 18, 2017
 *      Author: User
 */

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "CSVManager.h"
using namespace std;

CSVManager::CSVManager(string fileName, string PlatName, string flags){
	file = fileName + ".csv";
	PlatformName = PlatName;
	CompFlags = flags;
}

void CSVManager::writeLine(double bufSize, string testName, int cols, string dataType, long t){
	//get datetime as string
	ofstream f(file.c_str(), ios::out | ios::app );
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
	string datetime(buffer);

	char str[1024];
	sprintf(str, "%s,%s,%s,%lf,%s,%d,%s,%ld, %f",
		datetime.c_str(), PlatformName.c_str(), CompFlags.c_str(),
		bufSize, testName.c_str(), cols, dataType.c_str(), t, 
		100.0 * (float)t / (float)bufSize);

	puts(str);

	f << str << endl;
	f.close();
}
