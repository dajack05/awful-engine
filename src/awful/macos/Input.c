#include <awful/Global.h>

#ifdef __MACOS__

#include <awful/Input.h>
#include <stdio.h>

int InputGetChar() {
  int c = getchar();
  return c;
}

#endif