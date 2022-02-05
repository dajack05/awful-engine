#include <awful/Display.h>

#define GRADIENT_LENGTH ((sizeof(Gradient) / sizeof(char)) - 1)
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