#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <math.h>

#include  "TimeManagerWindows.h" //will eventually replace this with OS code
using namespace std;

template <typename T>
void matrixSum(int size, int cols, T signal){ //T signal only serves to designate the variable type for the function - it doesn't do anything inside the function itself

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

  free(buf);
}

template <typename T>
void matrixMultiply(int size, T signal){
	int numElements = size/sizeof(T);
	numElements /= 3; //we're splitting the buffer between 3 matrixes, so numElements will be the number of elements in each matrix
	int n = (int)sqrt(numElements); //all the matricies will be square, so each matrix will be NxN
	numElements = n*n; //Since we rounded down n to the nearest int, we update the value of numElements to make sure it's correct

	T *buf = (T*)malloc(size);
	T *buf2 = buf + numElements;
	T *bufRes = buf2 + numElements;

	// Set everything to an initial value
	int r, c;
	for (r = 0; r < n; r++) {
	  T *rp = buf + r*n;
	  T *rp2 = buf2 + r*n;
	  for (c = 0; c < n; c++) {
	    rp[c] = (T)(r+c);
	    rp2[c] = (T)(n-r-c);
	  }
	}

	//Multiply the matrixes at buf and buf2 and put the result in bufRes
	for (int i = 0; i < numElements; i++){
		//get the current row and column
		r = i / n;
		c = i % n;
		bufRes[i] = 0;
		for(int j = 0; j < n; j++){
			bufRes[i] += buf[r*n + j] + buf2[j*n + c];
		}
	}

	// Sum the total result matrix to make sure compiler doesn't optimize code away
	int total = 0;
	for (c = 0; c < numElements; c++) total += bufRes[c];

	free(buf);
}

//for testing
int main(int argc, char *argv[])
{
  TimeManager tm = TimeManager();
  if (argc != 3) {
    printf("Args: #size #col\n");
    return -1;
  }

  int size = atoi(argv[1]);
  int cols = atoi(argv[2]);

  tm.start();
  matrixSum(size, cols, 5);
  tm.end();

  std::cout << "Time Elapsed For Sum = " << tm.getInterval() << endl;

  tm.start();
  matrixMultiply(size, 5);
  tm.end();

  std::cout << "Time Elapsed For Multiply = " << tm.getInterval() << endl;
}

