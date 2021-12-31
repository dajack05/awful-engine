#include <Global.h>

#include "assets.h"

#include <Display.h>
#include <System.h>
#include <Vector.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEG2RAD(a) (a * (M_PI / 180))

void sleepUntilFPS(u16 targetFPS, u64 startTime) {
  u64 now = SystemTime();
  double timePerFrame = 1000.0 / targetFPS;
  while ((double)(now - startTime) <= timePerFrame) {
    now = SystemTime();
  }
}

void Run() {

  struct WindowSize winsize = DisplayInit(false);

  struct Vector vec1 = vec_new(10, 10);
  struct Vector vec2 = vec_new(1, 2);

  bool should_run = true;
  while (should_run) {
    u64 startTime = SystemTime();
    double t = (double)startTime / 1000.0F;

    // vec1 = vec_addv(vec1, vec2);
    vec1 = vec_addv(vec1, vec2);

    DisplayClear();

    char str[128];
    sprintf(str, "%f, %f", vec1.x, vec1.y);
    DisplaySetStr(10, 10, str);

    DisplayPresent();
    sleepUntilFPS(10, startTime);
  }
}
