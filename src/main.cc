/*
 * main.cc
 *
 *  Created on: Nov 18, 2017
 *      Author: Caleb Nelson
 */

#include "matrixCalc.cc"
#include "CSVManager.h"

static const int CacheSizes[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 0 };
		
#define PLAT "Mac"

// Do a run of tests on a data type (e.g. "int"), into a csv
//		  
template <typename T>
void doRun(CSVManager csvm, string dtype, T signal) {

  long sum, avg;
  int s, i; 
  // Loop over buf sizes in .5m intervals
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 512 * 1024; //Multiply by .5 MB
    // Do 16 runs of Sum and average the results
    matrixSumTimer(bufSize, s*100, signal, 16, &sum, &avg);
    csvm.writeLine(s/2.0, "Sum", s*100, dtype, avg);
    // Multiply w/o blocking for 2 runs
    matrixMultiplyTimer(bufSize, 1, signal, 2, &sum, &avg);
    csvm.writeLine(s/2.0, "Mult01", 0, dtype, sum);
    // Multiply blocking by 32x32 squares for 2 runs
    matrixMultiplyTimer(bufSize, 32, signal, 2, &sum, &avg);
    csvm.writeLine(s/2.0, "Mult32", 0, dtype, sum);
    // Multiply blocking by 64x64 squares for 2 runs
    matrixMultiplyTimer(bufSize, 64, signal, 2, &sum, &avg);
    csvm.writeLine(s/2.0, "Mult64", 0, dtype, sum);
  }
}

// Main loop runs an identical set of tests for each of four data types
//
int main(int argc, char *argv[])
{
  string name = PLAT;

  CSVManager csvm1 = CSVManager("int", name, "");
  doRun(csvm1, "int", (int)0);

  CSVManager csvm2 = CSVManager("float", name, "");
  doRun(csvm2, "float", (float)0);

  CSVManager csvm3 = CSVManager("long", name, "");
  doRun(csvm3, "long", (long)0);

  CSVManager csvm4 = CSVManager("char", name, "");
  doRun(csvm4, "char", (char)0);
}
