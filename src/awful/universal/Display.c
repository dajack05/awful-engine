#include <awful/Display.h>

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