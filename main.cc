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
	CSVManager csvm = CSVManager("test1", "ASUS Laptop", "");
	int bufSize, signal = 0;
	double sum, avg;
	for (bufSize = 1; bufSize <= 10; bufSize += 0.5){
		matrixSumTimer(bufSize*1000000, bufSize*100, signal, 1, &sum, &avg);
		csvm.writeLine(bufSize, "Sum", bufSize*100, "int", sum);
		matrixMultiplyTimer(bufSize*1000000, signal, 1, &sum, &avg);
		csvm.writeLine(bufSize, "Multiply", 0, "int", sum);
	}
}
