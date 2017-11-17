#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include  "TimeManagerWindows.h" //will eventually replace this with OS code
using namespace std;

template <typename T>
void matrixSum(int size, int cols, T signal){

  int numElements = size/sizeof(T);
  int rows = (numElements / cols) - 1;

  // Allocate the space                                                                                                                     
  T *buf = (T*)malloc(size);
  // Results in the last row                                                                                                                
  T *res = buf + rows*cols;

  // Set everything to an initial value
  int r, c;                                                                                                     
  for (r = 0; r < rows; r++) {
    T *rp = buf + r*cols;
    for (c = 0; c < cols; c++) {
      rp[c] = (T)(r+c);
    }
  }

  // Loop by column, putting sum in the last row                                                                                            
  for (c = 0; c < cols; c++) {
    int sum = 0;
    for (r = 0; r < rows; r++) {
      sum += buf[r*cols + c];
    }
    res[c] = sum;
  }

  // Sum the total result line to make sure compiler doesn't optimize code away                                                             
  int total = 0;
  for (c = 0; c < cols; c++) total += res[c];

}

//for testing
int main(int argc, char *argv[])
{
  TimeManager tm = TimeManager();
  if (argc != 3) {
    printf("Args: #row #col\n");
    return -1;
  }

  tm.start();
  int cols = atoi(argv[1]);
  int size = atoi(argv[2]);
  matrixSum(size, cols, 5);
  tm.end();

  std::cout << "Time Elapsed = " << tm.getInterval();
}

