/*
 * main.cc
 *
 *  Created on: Nov 18, 2017
 *      Author: User
 */

#include "matrixCalc.cc"
#include "CSVManager.h"

static const int CacheSizes[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 0 };
				  
int main(int argc, char *argv[])
{
  string name = "Mac";
  CSVManager csvm1 = CSVManager("int", name, "");
  int signal1 = 0;
  long sum, avg;
  int s, i; 
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 500 * 1024; //Multiply by .5 MB
    matrixSumTimer(bufSize, s*100, signal1, 16, &sum, &avg);
    csvm1.writeLine(s/2.0, "Sum", s*100, "int", avg);
    matrixMultiplyTimer(bufSize, signal1, 1, &sum, &avg);
    csvm1.writeLine(s/2.0, "Multiply", 0, "int", sum);
  }
  CSVManager csvm2 = CSVManager("float", name, "");
  float signal2 = 0;
  //long sum, avg;
  //int s, i; 
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 500 * 1024; //Multiply by .5 MB
    matrixSumTimer(bufSize, s*100, signal2, 16, &sum, &avg);
    csvm2.writeLine(s/2.0, "Sum", s*100, "float", avg);
    matrixMultiplyTimer(bufSize, signal2, 1, &sum, &avg);
    csvm2.writeLine(s/2.0, "Multiply", 0, "float", sum);
  }
  CSVManager csvm3 = CSVManager("long", name, "");
  long signal3 = 0;
  //long sum, avg;
  //int s, i; 
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 500 * 1024; //Multiply by .5 MB
    matrixSumTimer(bufSize, s*100, signal3, 16, &sum, &avg);
    csvm3.writeLine(s/2.0, "Sum", s*100, "long", avg);
    matrixMultiplyTimer(bufSize, signal3, 1, &sum, &avg);
    csvm3.writeLine(s/2.0, "Multiply", 0, "long", sum);
  }
  CSVManager csvm4 = CSVManager("char", name, "");
  char signal4 = 0;
  //long sum, avg;
  //int s, i; 
  for (i = 0; (s = CacheSizes[i]) != 0; i++) {
    int bufSize = s * 500 * 1024; //Multiply by .5 MB
    matrixSumTimer(bufSize, s*100, signal4, 16, &sum, &avg);
    csvm4.writeLine(s/2.0, "Sum", s*100, "char", avg);
    matrixMultiplyTimer(bufSize, signal4, 1, &sum, &avg);
    csvm4.writeLine(s/2.0, "Multiply", 0, "char", sum);
  }
}
