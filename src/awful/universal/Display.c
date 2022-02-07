#include <awful/Display.h>
#include <awful/Sprite.h>
#include <awful/libs/cgm.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

char mBG[MAX_WIDTH * MAX_HEIGHT];
char mScreen[MAX_WIDTH * MAX_HEIGHT];
WindowSize mSize;

bool mWide = false;

#define GRADIENT_LENGTH ((sizeof(Gradient) / sizeof(char)) - 1)

void DisplaySetIsWide(bool wide) { mWide = wide; }

void DisplaySetSize(WindowSize size) { mSize = size; }

void wipeScreen() {
  for (u16 i = 0; i < mSize.width * mSize.height; i++) {
    if (mBG[i]) {
      mScreen[i] = mBG[i];
    } else {
      mScreen[i] = ' ';
    }
  }
}

char Gradient[] = "@%#*+=-:.";
void DrawGradientLine(CgmVec2 from, CgmVec2 to, float fromDepth,
                      float toDepth) {
  double dx = to.x - from.x;
  double dy = to.y - from.y;

  double length = fabs(dy);
  if (fabs(dx) >= length) {
    length = fabs(dx);
  }

  dx = dx / length;
  dy = dy / length;

  double gx = fabs((toDepth - fromDepth) / length);

  double x = from.x;
  double y = from.y;
  double g = fromDepth;

  int i = 0;
  while (i < length - 1) {
    x += dx;
    y += dy;
    g += gx;

    u8 gIdx = (u8)floor(g * GRADIENT_LENGTH);
    DisplaySetChar((u16)x, (u16)y, Gradient[gIdx]);
    i++;
  }
}

void DrawLine(CgmVec2 from, CgmVec2 to) {
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

void DisplaySetInt(u16 x, u16 y, const int value) {
  char str[16];
  sprintf(str, "%d", value);
  DisplaySetStr(x, y, str);
}

void DisplaySetFloat(u16 x, u16 y, const float value) {
  char str[16];
  sprintf(str, "%f", value);
  DisplaySetStr(x, y, str);
}

void DisplayPresent() {
  if (mWide) {
    // Double size blocks
    for (u16 i = 0; i < mSize.width * mSize.height; i++) {
      printf("%c%c", mScreen[i], mScreen[i]);
      if (i % mSize.width == mSize.width - 1) {
        printf("\r\n");
      }
    }
  } else {
    // Standard blocks
    for (u16 i = 0; i <= mSize.width * mSize.height; i++) {
      printf("%c", mScreen[i]);

      // Are we at the end of the line?
      if (i % mSize.width == mSize.width - 1) {
        // Make sure we're NOT at the last line
        if (i < mSize.width * mSize.height - mSize.width) {
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
  if (x > 0 && x <= mSize.width && y > 0 && y <= mSize.height) {
    mScreen[x + y * mSize.width] = c;
  }
}

void DisplaySetStr(u16 x, u16 y, const char *str) {
  u16 idx = x + y * mSize.width;
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
        if (finalx < mSize.width && finaly < mSize.height && finalx >= 0 &&
            finaly >= 0) {
          DisplaySetChar(finalx, finaly, sprite->data[idx]);
        }
      }
    }
  }
}

WindowSize *DisplayGetSize() { return &mSize; }

char* DisplayGetScreen(){
  return mScreen;
}