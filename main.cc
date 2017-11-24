/*
 * main.cc
 *
 *  Created on: Nov 18, 2017
 *      Author: User
 */

#include "matrixCalc.cc"
#include "CSVManager.h"

int main(int argc, char *argv[])
{
	CSVManager csvm = CSVManager("test1", "Raspberry Pi", "");
	int bufSize = 0;
	int signal = 0;
	long sum, avg;
	for (bufSize = 1; bufSize <= 20; bufSize += 1){
		matrixSumTimer(bufSize*102400, bufSize*100, signal, 12, &sum, &avg);
		csvm.writeLine(bufSize, "Sum", bufSize*100, "int", avg);
		//matrixMultiplyTimer(bufSize*102400, signal, 1, &sum, &avg);
		//csvm.writeLine(bufSize, "Multiply", 0, "int", sum);
	}
}
