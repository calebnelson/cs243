/*
 * virtos.cc
 *
 *  Created on: Nov 16, 2017
 *      Author: Caleb Nelson
 *
 * Abstract things we need from the local OS
 *  that currently have the same defintion across all platforms
 */

#include "virtos.h"
#include <time.h>

// Get time right now as a string
//
string VirtOs::now() {

  time_t rawtime;
  time (&rawtime);

  struct tm * timeinfo;
  timeinfo = localtime(&rawtime);

  char buffer[80];
  strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);

  return string(buffer);
}
