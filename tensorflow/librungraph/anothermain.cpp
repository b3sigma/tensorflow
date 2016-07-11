#include <stdio.h>
#include "librungraph.h"

int main(void) {

  float a = 2.0f;
  float b = 99.0f;
  float c = -1.0f;
  bool result = false; // testfunction(a, b, c);

  printf("We got a=%f b=%f c=%f, res=%d\n",
      a, b, c, result);

  return 0;
}
