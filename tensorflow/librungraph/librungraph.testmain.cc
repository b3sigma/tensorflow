#include <stdio.h>
#include <stdlib.h>

#define _GR_NO_EXTERN_
#include "librungraph.h"

int main(int argc, char* argv[]) {
  float a = 19.5f;
  float b = 2.3f;
  float c = -1.0f;
  bool success = testfunction(a, b, c);

  printf("from graphlibmain, got a=%f, b=%f, c=%f, succes=%d",
      a, b, c, success);

  return 0;
}
