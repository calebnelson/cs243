/*
 * virtos.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Caleb Nelson
 *
 * Abstract things we need from the local OS
 */

#include <cstring>
#include <string>

using namespace std;

// List of supported platforms
// Make sure one is defined
//
#define myWIN 1
#define myLIN 2

#ifndef myPLAT
#define myPLAT myLIN
#endif

// Performance timer class 
//
class Timer {
 public:
  Timer();	// Require construct/destruct in case impl must alloc
  ~Timer();
  void begin(); // Start or restart a timer
  long delta(); // Elpased time from start to now

 private:
  void *ptr;	// Place for the implementations to store data
  long val;
};

// Other OS abstractions
//
class VirtOs {
 public:
  static void pause();
  static string now();
};
