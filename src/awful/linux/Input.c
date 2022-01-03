#include <awful/Global.h>

#ifdef __LINUX__

#include <awful/Input.h>
#include <unistd.h>

char InputGetChar() {
  char c;
  read(STDIN_FILENO, &c, 1);
  return c;
}

#endif