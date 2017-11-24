#include "virtos.h"

#if myPLAT == myLIN

#include <stdlib.h>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock::time_point HTP;

Timer::Timer() { 
  ptr = (void*)malloc(sizeof(HTP));
}

Timer::~Timer() { 
  if (ptr) free(ptr);
}

void Timer::begin() {
  HTP tt = high_resolution_clock::now();
  *(HTP*)ptr = tt;
}

long Timer::delta() {
  HTP t1 = *(HTP*)ptr;
  HTP t2 = high_resolution_clock::now();
  microseconds us = duration_cast<microseconds>(t2 - t1);
  return (long)us.count();
}

void VirtOs::pause() {
  // ToDo
}

#endif
