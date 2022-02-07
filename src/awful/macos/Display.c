#include <awful/Global.h>

#ifdef __MACOS__

#include <awful/Display.h>
#include <awful/Sprite.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

char mBG[MAX_WIDTH * MAX_HEIGHT];
char mScreen[MAX_WIDTH * MAX_HEIGHT];
u16 mWidth = 0;
u16 mHeight = 0;

bool mWide = false;

struct termios orig_termios;

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void wipeScreen() {
  for (u16 i = 0; i < mWidth * mHeight; i++) {
    mScreen[i] = mBG[i];
  }
}

struct WindowSize DisplayInit(bool wide) {
  enableRawMode();
  mWide = wide;

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  mWidth = w.ws_col;
  mHeight = w.ws_row;

  for (u16 i = 0; i < mWidth * mHeight; i++) {
    mBG[i] = ' ';
  }

  wipeScreen();

  struct WindowSize ws;
  ws.width = mWidth;
  ws.height = mHeight;

  return ws;
}

void DisplayClear() { system("clear"); }

#endif