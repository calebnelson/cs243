#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include  "TimeManagerWindows.cc" //will eventually replace this with OS code

template <typename T>
void matrixSum(int cols, int size, T signal){

  int rows = (size / cols) - 1;

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
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  matrixSum(rows, cols, 5);
  tm.end();

  cout << "Time Elapsed = " << tm.getInterval();
}

