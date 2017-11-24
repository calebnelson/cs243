/*
 * main.cc
 *
 *  Created on: Nov 18, 2017
 *      Author: User
 */

#include "matrixCalc.cc"
#include "CSVManager.h"

static const int CacheSizes[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
				  20, 24, 28, 32, 36, 40, 44, 48,
				  64, 128, 192, 256, 0 };
				  
int main(int argc, char *argv[])
{
  CSVManager csvm = CSVManager("test1", "Raspberry Pi", "");
  int signal = 0;
  long sum, avg;
  int s, i; 
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 64 * 1024;
    matrixSumTimer(bufSize, s*100, signal, 16, &sum, &avg);
    csvm.writeLine(bufSize, "Sum", s*100, "int", avg);
    //matrixMultiplyTimer(bufSize*102400, signal, 1, &sum, &avg);
    //csvm.writeLine(bufSize, "Multiply", 0, "int", sum);
  }
}
