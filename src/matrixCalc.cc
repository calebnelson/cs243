#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include  "virtos.h" //will eventually replace this with OS code
using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))

// matrixSum() sums up the columsn of a matrix into a results row
//   matrix is of type <signal>, total #bytes <size>, columns <cols>
//
// Allocates a block of contiguous space, calculates #rows including an
// additional results row at the end, fills the matrix wih values, then 
// sums each column into the results row.
//
template <typename T>
int matrixSum(int size, int cols, T signal){ 

  int numElements = size/sizeof(T);
  int rows = (numElements / cols) - 1;

  // Allocate the space                                                                                                                     
  T *buf = (T*)malloc(size);
  // Results in the last row                                                                                                                
  T *res = buf + rows*cols;

  // Set everything to an initial value
  int r, c, x;                                                                                                     
  for (x = 0, r = 0; r < rows; r++) {
    for (c = 0; c < cols; c++, x++) {
      buf[x] = (T)(r+c) + signal;
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

  // Do something with the data so compiler doesn't optimize code away                                                             
  int total = 0;
  for (c = 0; c < cols; c++) total += res[c];

  free(buf);
  return total;
}

// Time <repitition> runs of Sum, returning total and average time clicks
// TODO: only allocate and fill the memory once, not for each repitition
//
template <typename T>
void matrixSumTimer(int size, int cols, T signal, int repitions, long *sum, long *avg){
  Timer tm = Timer();
  *sum = 0.0;
  for(int i = 0; i < repitions; i++){
    tm.begin();
    matrixSum(size, cols, signal);
    *sum += tm.delta();
  }
  *avg = *sum/repitions;
}

// matrixMultiply multiplies two square matrices into a 3rd results matrix
//  <size> is total #bytes, <block> is the blocking factor when looping, <signal> is the type
//
// Allocates a block of contiguous space, gives 1/3 for each matrix, calculates shared #rows/cols,
// fills the source matrices with initial values, then loops through each r,c position in the
// result filling it with sum of Source1[Row(r)] * Source2[Col(c)]
// 
// Rather then a simple loop of all rows by all cols, block factor allows calculating blocks of
// results (e.g. [rows(0:31) x cols(0:31)], followed by [rows(32:63) x cols (0:31)] and so on
// This blocking should have better cache usage as long as all the data for the set of rows and 
// cols fit in the cache at once. By contrast, if we just looped over all cols, the first col
// would be gone from the cache by the time we increment to the next row.
//
template <typename T>
int matrixMultiply(int size, int block, T signal){
  int numElements = size/sizeof(T);
  numElements /= 3; //we're splitting the buffer between 3 matrixes, so numElements will be the number of elements in each matrix
  int n = (int)sqrt(numElements); //all the matricies will be square, so each matrix will be NxN
  numElements = n*n; //Since we rounded down n to the nearest int, we update the value of numElements to make sure it's correct
  
  // Allocate the space and distribute across the three equal sized square matrices
  T *buf1 = (T*)malloc(size);
  T *buf2 = buf1 + numElements;
  T *bufR = buf2 + numElements;
  
  // Set sources to an initial value
  int x, r, c;
  x = 0;
  for (r = 0; r < n; r++) {
    for (c = 0; c < n; c++) {
      buf1[x] = (T)(r+c);
      buf2[x] = (T)(n-r-c);
      x += 1;
    }
  }
  
  // Make sure we have a reasonable blocking factor
  if (block <= 0) block = 1;
  
  // Process the matrix in blocks to preserve cache 
  // TODO: Explore whether it would be better to loop by c/r instead of r/c
  for (r = 0; r < n; r += block) {
    for (c = 0; c < n; c += block) {
      // Calculate actual last r,c in the block
      int rTgt = min(r + block, n);
      int cTgt = min(c + block, n);
      for (int rx = r; rx < rTgt; rx++) {
	// Start of results for this row in the block
	int x = rx * n + c;
	for (int cx = c; cx < cTgt; cx++) {
	  bufR[x] = 0;
	  for(int j = 0; j < n; j++) {
	    bufR[x] += buf1[rx*n + j] + buf2[j*n + cx];
	  }
	  x += 1;
	}
      }
    }
  }
  
  // Do something with the data so compiler doesn't optimize code away                                                             
  int total = 0;
  for (c = 0; c < n; c++) total += bufR[c];

  free(buf1);

  return total;
}

// Time <repitition> runs of Multiply, returning total and average time clicks
// TODO: only allocate and fill the memory once, not for each repitition
//
template <typename T>
void matrixMultiplyTimer(int size, int block, T signal, int repitions, long *sum, long *avg){
  Timer tm = Timer();
  *sum = 0.0;
  for(int i = 0; i < repitions; i++){
    tm.begin();
    matrixMultiply(size, block, signal);
    *sum += tm.delta();
  }
  *avg = *sum/repitions;
}

//for testing
/*int main(int argc, char *argv[])
{
  Timer tm = Timer();
  if (argc != 3) {
    printf("Args: #size #col\n");
    return -1;
  }

  int size = atoi(argv[1]);
  int cols = atoi(argv[2]);

  long sum = 0, avg = 0;

  tm.begin();
  matrixSum(size, cols, 5);
  std::cout << "Time Elapsed For Sum = " << tm.delta() << endl;

  tm.end();
  matrixMultiply(size, 1, 5);
  std::cout << "Time Elapsed For Multiply = " << tm.delta() << endl;

  matrixSumTimer(size, cols, 5, 5, &sum, &avg);
  std::cout << "Time Elapsed For 5x Sum = " << sum << " Avg: " << avg << endl;

  matrixMultiplyTimer(size, 5, 5, &sum, &avg);
  std::cout << "Time Elapsed For 5x Multiply = " << sum << " Avg: " << avg << endl;
}*/

