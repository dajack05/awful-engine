#include <awful/Global.h>

#ifdef __MACOS__

#include <awful/Display.h>
#include <awful/Input.h>
#include <unistd.h>

bool downKeys[128];

void pollInput() {

  for (int i = 0; i < 128; i++) {
    downKeys[i] = false;
  }

  char c = 0;
  read(STDIN_FILENO, &c, 1);

  if (c > 0) {
    downKeys[c] = true;
  }
}

bool isKeyDown(char code) {
  if (code > 0) {
    return downKeys[code];
  }

  return false;
}

#endif