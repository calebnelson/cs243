#include "virtos.h"

#if myPLAT == myWIN

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

Timer::Timer() { 
  ptr = (void*)malloc(sizeof(LARGE_INTEGER));
}

Timer::~Timer() { 
  if (ptr) free(ptr);
}

void Timer::begin() {
  LARGE_INTEGER *bgp = (LARGE_INTEGER *)ptr;
  QueryPerformanceCounter(bgp);
}

long Timer::delta() {
  LARGE_INTEGER *bgp = (LARGE_INTEGER *)ptr;
  LARGE_INTEGER ed;
  QueryPerformanceCounter(&ed);
  return (long)(ed.QuadPart - bgp->QuadPart);
}

// Pause the process briefly
//
void VirtOs::pause() {
  Sleep(1);
}

#endif
