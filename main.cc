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
	int bufSize = 0;
	int signal = 0;
	long sum, avg;
	for (bufSize = 1; bufSize <= 20; bufSize += 1){
		matrixSumTimer(bufSize*500000, bufSize*100, signal, 1, &sum, &avg);
		csvm.writeLine(bufSize, "Sum", bufSize*100, "int", sum);
		matrixMultiplyTimer(bufSize*500000, signal, 1, &sum, &avg);
		csvm.writeLine(bufSize, "Multiply", 0, "int", sum);
	}
}
