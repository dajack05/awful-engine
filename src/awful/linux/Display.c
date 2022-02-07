#include <awful/Global.h>

#ifdef __LINUX__

#include <awful/Display.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

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

void DisplayInit() {
  enableRawMode();

  struct winsize w;
  WindowSize win;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  win.width = w.ws_col;
  win.height = w.ws_row;
  DisplaySetSize(win);

  wipeScreen();
}

void DisplayClear() {
  system("clear");
}

#endif