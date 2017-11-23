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

void CSVManager::writeLine(int bufSize, string testName, int cols, string dataType, double time){
	//get datetime as string
	ofstream f(file);
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
	string datetime(buffer);

	string str = datetime + "," +
			PlatformName + "," +
			CompFlags + "," +
			std::to_string(bufSize) + "," +
			testName + ",";

	//insert cols only if it's a positive number (a zero or negative number usually means it's unused, i.e. multiply was called instead
	if (cols <= 0){
		str = str + ",";
	}
	else{
		str = str + to_string(cols) + ",";
	}

	str = str + dataType + "," + to_string(time) + ",";

	f << str << endl;
	f.close();
}
