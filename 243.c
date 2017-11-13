#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

double gridCalc(int rows, int cols){

  int r = rows;
  int c = cols;
  int size = (rows+1)*cols;

  // Allocate the space                                                                                                                     
  unsigned char *buf = (unsigned char*)malloc(size);
  // Results in the last row                                                                                                                
  unsigned char *res = buf + rows*cols;

  // Set everything to an initial value                                                                                                     
  for (r = 0; r < rows; r++) {
    unsigned char *rp = buf + r*cols;
    for (c = 0; c < cols; c++) {
      rp[c] = (unsigned char)(r+c);
    }
  }

  LARGE_INTEGER frequency;
  LARGE_INTEGER start;
  LARGE_INTEGER end;
  double interval;
  
  QueryPerformanceFrequency(&frequency);
  QueryPerformanceCounter(&start);

  // Loop by column, putting sum in the last row                                                                                            
  for (c = 0; c < cols; c++) {
    int sum = 0;
    for (r = 0; r < rows; r++) {
      sum += buf[r*cols + c];
    }
    res[c] = sum;
  }
  
  QueryPerformanceCounter(&end);
  interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

  // Sum the total result line to make sure compiler doesn't optimize code away                                                             
  int total = 0;
  for (c = 0; c < cols; c++) total += res[c];

  return interval;
}

double gridCalcXTimes(int rows, int cols, int x){
  double sum = 0;
  double step = 0;
  int i = 0;
  for (i = 0; i < x; i++){
    step = gridCalc(rows, cols);
    sum += step;
  }
  return (sum);
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("Args: #row #col\n");
    return -1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  double time = gridCalcXTimes(rows, cols, 5);
  printf("Avg time for 5 runs = %f", time);

}
