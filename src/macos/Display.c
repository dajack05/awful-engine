#include <Global.h>

#ifdef __MACOS__

#include <Display.h>
#include <stdio.h>
#include <string.h>

char mBG[MAX_WIDTH * MAX_HEIGHT];
char mScreen[MAX_WIDTH * MAX_HEIGHT];
u8 mWidth = 0;
u8 mHeight = 0;

bool mWide = false;

void wipeScreen() {
  for (u16 i = 0; i < mWidth * mHeight; i++) {
    mScreen[i] = mBG[i];
  }
}

void DisplayInit(u8 width, u8 height, bool wide) {
  mWidth = width;
  mHeight = height;
  mWide = wide;

  for (u16 i = 0; i < mWidth * mHeight; i++) {
    mBG[i] = ' ';
  }

  wipeScreen();
}

void DisplayPresent() {
  if (mWide) {
    // Double size blocks
    for (u16 i = 0; i < mWidth * mHeight; i++) {
      printf("%c%c", mScreen[i], mScreen[i]);
      if (i % mWidth == mWidth - 1) {
        printf("\n");
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
          printf("\n");
        }
      }
    }
  }

  wipeScreen();
}

void DisplaySetChar(u8 x, u8 y, char c) { mScreen[x + y * mWidth] = c; }

void DisplaySetStr(u8 x, u8 y, const char *str) {
  u16 idx = x + y * mWidth;
  for (u16 i = 0; i < strlen(str); i++) {
    mScreen[idx + i] = str[i];
  }
}

void DrawSprite(struct Sprite *sprite) {
  for (int y = 0; y < sprite->h; y++) {
    for (int x = 0; x < sprite->w; x++) {
      int idx = x + y * sprite->w;
      // Skip if we're 'transparent'
      if (sprite->data[idx] != ' ') {
        int finalx = (int)sprite->x + x;
        int finaly = (int)sprite->y + y;

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
    printf("\n");
  }
}

void DrawLine(u8 x0, u8 y0, u8 x1, u8 y1) {
  float x, y, dx, dy, steps;
  dx = (float)(x1 - x0);
  dy = (float)(y1 - y0);
  if (dx >= dy) {
    steps = dx;
  } else {
    steps = dy;
  }
  dx = dx / steps;
  dy = dy / steps;
  x = x0;
  y = y0;
  float i = 1;
  while (i <= steps) {
    DisplaySetChar(x, y, '*');
    x += dx;
    y += dy;
    i = i + 1;
  }
}

// void DrawLine(u8 x0, u8 y0, u8 x1, u8 y1) {
//   char c = '*';

//   int dx = x1 - x0;
//   int dy = y1 - y0;
//   int p = 2 * dy - dx;
//   int x = x0;
//   int y = y0;

//   while (x < x1) {
//     if (p >= 0) {
//       DisplaySetChar(x, y, c);
//       y = y + 1;
//       p = p + 2 * dy - 2 * dx;
//     } else {
//       DisplaySetChar(x, y, c);
//       p = p + 2 * dy;
//     }
//     x = x + 1;
//   }
// }

#endif