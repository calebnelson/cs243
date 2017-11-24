
#include "virtos.h"
#include <stdio.h>

int main(int argc, char**argv)
{
  Timer t;
  t.begin();
  for (int i = 0; i < 10000; i++)
    argc += i;
  printf("Time: %ld, %d, %s\n", t.delta(), argc, VirtOs::now().c_str());
}
