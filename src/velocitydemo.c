#include "velocitydemo.h"
#include "assets.h"

#include <awful/Display.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sleepUntilFPS(u16 targetFPS, u64 startTime) {
  u64 now = SystemTime();
  double timePerFrame = 1000.0 / targetFPS;
  while ((double)(now - startTime) <= timePerFrame) {
    now = SystemTime();
  }
}

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  struct Sprite player;
  player.pos = vec2f_new(((float)winSize.width / 2) - 10,
                         ((float)winSize.height / 2) - 7);
  player.size = vec2i_new(20, 13);
  player.data = SPHERE;

  const struct Vec2f grav = vec2f_new(0, 1);

  bool should_run = true;
  while (should_run) {
    u64 startTime = SystemTime();
    double t = (double)startTime / 1000.0F;

    DisplayClear();

    DrawSprite(&player);

    DisplayPresent();
    sleepUntilFPS(10, startTime);
  }
}
