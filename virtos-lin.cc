#include "virtos.h"

#if myPLAT == myLIN

#include <time.h>
#include <mach/mach_time.h>
#include <unistd.h>

Timer::Timer() { }

Timer::~Timer() { }

void Timer::begin() {
  val = (long)mach_absolute_time();
}

long Timer::delta() {
  long now = (long)mach_absolute_time();
  return now - val;
}

void VirtOs::pause() {
  // ToDo
}

#endif
