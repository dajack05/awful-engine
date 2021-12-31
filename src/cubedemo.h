#include <Global.h>

#include "assets.h"

#include <Display.h>
#include <System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define DEG2RAD(a) (a * (M_PI / 180))

#define BOX_SIZE 8

struct Point {
  float x;
  float y;
};

void sleepUntilFPS(u16 targetFPS, u64 startTime) {
  u64 now = SystemTime();
  double timePerFrame = 1000.0 / targetFPS;
  while ((double)(now - startTime) <= timePerFrame) {
    now = SystemTime();
  }
}

void Run() {

  struct WindowSize winsize = DisplayInit(false);

  DisplaySetChar(1, 1, ' ');

  struct Point p[8];

  struct Point offset;
  offset.x = 0;
  offset.y = 0;

  bool should_run = true;
  while (should_run) {
    u64 startTime = SystemTime();
    double t = (double)startTime / 1000.0F;

    DisplayClear();

    // Update
    offset.x = (float)sin(t) * 4;

    // Small
    p[0].x = offset.x + (winsize.width / 2) + (float)sin(t) * BOX_SIZE * 2;
    p[0].y = offset.y + (winsize.height / 2) + (float)cos(t) * BOX_SIZE;

    p[1].x = offset.x + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(90)) * BOX_SIZE * 2;
    p[1].y = offset.y + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(90)) * BOX_SIZE;

    p[2].x = offset.x + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(180)) * BOX_SIZE * 2;
    p[2].y = offset.y + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(180)) * BOX_SIZE;

    p[3].x = offset.x + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(270)) * BOX_SIZE * 2;
    p[3].y = offset.y + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(270)) * BOX_SIZE;

    // Large
    p[4].x =
        (offset.x * 2) + (winsize.width / 2) + (float)sin(t) * BOX_SIZE * 4;
    p[4].y =
        (offset.y * 2) + (winsize.height / 2) + (float)cos(t) * BOX_SIZE * 2;
    p[5].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(90)) * BOX_SIZE * 4;
    p[5].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(90)) * BOX_SIZE * 2;
    p[6].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(180)) * BOX_SIZE * 4;
    p[6].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(180)) * BOX_SIZE * 2;
    p[7].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + DEG2RAD(270)) * BOX_SIZE * 4;
    p[7].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + DEG2RAD(270)) * BOX_SIZE * 2;

    // Draw
    DrawLine(p[0].x, p[0].y, p[1].x, p[1].y);
    DrawLine(p[1].x, p[1].y, p[2].x, p[2].y);
    DrawLine(p[2].x, p[2].y, p[3].x, p[3].y);
    DrawLine(p[3].x, p[3].y, p[0].x, p[0].y);

    DrawLine(p[0 + 4].x, p[0 + 4].y, p[1 + 4].x, p[1 + 4].y);
    DrawLine(p[1 + 4].x, p[1 + 4].y, p[2 + 4].x, p[2 + 4].y);
    DrawLine(p[2 + 4].x, p[2 + 4].y, p[3 + 4].x, p[3 + 4].y);
    DrawLine(p[3 + 4].x, p[3 + 4].y, p[0 + 4].x, p[0 + 4].y);

    DrawLine(p[0].x, p[0].y, p[0 + 4].x, p[0 + 4].y);
    DrawLine(p[1].x, p[1].y, p[1 + 4].x, p[1 + 4].y);
    DrawLine(p[2].x, p[2].y, p[2 + 4].x, p[2 + 4].y);
    DrawLine(p[3].x, p[3].y, p[3 + 4].x, p[3 + 4].y);

    DisplayPresent();
    sleepUntilFPS(10, startTime);
  }
}
