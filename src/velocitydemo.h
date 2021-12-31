#include "assets.h"

#include <awful/Display.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void sleepUntilFPS(u16 targetFPS) {
  char cmd[32];
  sprintf(cmd, "sleep %f", 1.0F / targetFPS);
  system(cmd);
}

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  struct Sprite player;
  struct Vec2f velocity = vec2f_new(0.0F, 0.0F);
  player.pos = vec2f_new(((float)winSize.width / 2) - 10, 0);
  player.size = vec2i_new(20, 13);
  player.data = SPHERE;

  bool should_run = true;
  while (should_run) {

    if (player.pos.y > (float)(winSize.height - player.size.y) ||
        player.pos.y < 0) {
      velocity.y = -velocity.y;
    }
    if (player.pos.x > (float)(winSize.width - player.size.x) ||
        player.pos.x < 0) {
      velocity.x = -velocity.x;
    }

    player.pos = vec2f_addv(player.pos, velocity);

    DisplayClear();

    DrawSprite(&player);

    DisplayPresent();

    sleepUntilFPS(20);
  }
}
