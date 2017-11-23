/*
 * CSVManager.h
 *
 *  Created on: Nov 19, 2017
 *      Author: User
 */

#ifndef CSVMANAGER_H_
#define CSVMANAGER_H_

#include<iostream>
#include<string> // for string class

using namespace std;

class CSVManager{

	public:
		string PlatformName;
		string CompFlags;
		string file;

		CSVManager(string fileName, string PlatName, string flags);
		~CSVManager();
		void writeLine(int bufSize, string testName, int cols, string dataType, double time);

};


#endif /* CSVMANAGER_H_ */
