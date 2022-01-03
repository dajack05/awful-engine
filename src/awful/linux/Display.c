#include <awful/Global.h>

#ifdef __LINUX__

#include <awful/Display.h>
#include <awful/Sprite.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
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

void DisplayPresent() {
  if (mWide) {
    // Double size blocks
    for (u16 i = 0; i < mWidth * mHeight; i++) {
      printf("%c%c", mScreen[i], mScreen[i]);
      if (i % mWidth == mWidth - 1) {
        printf("\r\n");
      }
    }
  } else {
    // Standard blocks
    for (u16 i = 0; i <= mWidth * mHeight; i++) {
      printf("%c", mScreen[i]);

      // Are we at the end of the line?
      if (i % mWidth == mWidth - 1) {
        // Make sure we're NOT at the last line
        if (i < mWidth * mHeight - mWidth) {
          printf("\r\n");
        }
      }
    }
  }

  wipeScreen();

  // This can be better...
  usleep(1000000 / TARGET_FPS);
}

void DisplaySetChar(u16 x, u16 y, char c) {
  if (x > 0 && x <= mWidth && y > 0 && y <= mHeight) {
    mScreen[x + y * mWidth] = c;
  }
}

void DisplaySetStr(u16 x, u16 y, const char *str) {
  u16 idx = x + y * mWidth;
  for (u16 i = 0; i < strlen(str); i++) {
    mScreen[idx + i] = str[i];
  }
}

void DrawSprite(struct Sprite *sprite) {
  for (int y = 0; y < sprite->size.y; y++) {
    for (int x = 0; x < sprite->size.x; x++) {
      int idx = x + y * sprite->size.x;
      // Skip if we're 'transparent'
      if (sprite->data[idx] != ' ') {
        int finalx = (int)sprite->pos.x + x;
        int finaly = (int)sprite->pos.y + y;

        // Don't draw out of bounds
        if (finalx < mWidth && finaly < mHeight && finalx >= 0 && finaly >= 0) {
          DisplaySetChar(finalx, finaly, sprite->data[idx]);
        }
      }
    }
  }
}

void DisplayClear() {
  for (int i = 0; i < mHeight; i++) {
    printf("\r\n");
  }
}

void DrawLine(struct Vec2f from, struct Vec2f to) {
  const char c = '*';
  double dx = to.x - from.x;
  double dy = to.y - from.y;

  double length = fabs(dy);
  if (fabs(dx) >= length) {
    length = fabs(dx);
  }

  dx = dx / length;
  dy = dy / length;

  double x = from.x;
  double y = from.y;

  DisplaySetChar((u16)x, (u16)y, c);
  int i = 1;
  while (i <= length) {
    x += dx;
    y += dy;
    DisplaySetChar((u16)x, (u16)y, c);
    i++;
  }
}

#endif