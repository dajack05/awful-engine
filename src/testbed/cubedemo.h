#include <awful/Global.h>

#include "assets.h"

#include <awful/Display.h>
#include <awful/System.h>
#include <awful/cgm.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BOX_SIZE 8
// #define M_PI 3.1415

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

  CgmVec2 p[8];

  CgmVec2 offset = CgmVec2_init(0,0);

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
             (float)sin(t + cgm_degrees_to_radians(90)) * BOX_SIZE * 2;
    p[1].y = offset.y + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(90)) * BOX_SIZE;

    p[2].x = offset.x + (winsize.width / 2) +
             (float)sin(t + cgm_degrees_to_radians(180)) * BOX_SIZE * 2;
    p[2].y = offset.y + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(180)) * BOX_SIZE;

    p[3].x = offset.x + (winsize.width / 2) +
             (float)sin(t + cgm_degrees_to_radians(270)) * BOX_SIZE * 2;
    p[3].y = offset.y + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(270)) * BOX_SIZE;

    // Large
    p[4].x =
        (offset.x * 2) + (winsize.width / 2) + (float)sin(t) * BOX_SIZE * 4;
    p[4].y =
        (offset.y * 2) + (winsize.height / 2) + (float)cos(t) * BOX_SIZE * 2;
    p[5].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + cgm_degrees_to_radians(90)) * BOX_SIZE * 4;
    p[5].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(90)) * BOX_SIZE * 2;
    p[6].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + cgm_degrees_to_radians(180)) * BOX_SIZE * 4;
    p[6].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(180)) * BOX_SIZE * 2;
    p[7].x = (offset.x * 2) + (winsize.width / 2) +
             (float)sin(t + cgm_degrees_to_radians(270)) * BOX_SIZE * 4;
    p[7].y = (offset.y * 2) + (winsize.height / 2) +
             (float)cos(t + cgm_degrees_to_radians(270)) * BOX_SIZE * 2;

    // Draw
    DrawLine(p[0], p[1]);
    DrawLine(p[1], p[2]);
    DrawLine(p[2], p[3]);
    DrawLine(p[3], p[0]);

    DrawLine(p[0 + 4], p[1 + 4]);
    DrawLine(p[1 + 4], p[2 + 4]);
    DrawLine(p[2 + 4], p[3 + 4]);
    DrawLine(p[3 + 4], p[0 + 4]);

    DrawLine(p[0], p[0 + 4]);
    DrawLine(p[1], p[1 + 4]);
    DrawLine(p[2], p[2 + 4]);
    DrawLine(p[3], p[3 + 4]);

    DisplayPresent();
    sleepUntilFPS(10, startTime);
  }
}
