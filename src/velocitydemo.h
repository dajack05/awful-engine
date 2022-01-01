#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  struct Sprite player;
  struct Vec2f velocity = vec2f_new(2.0F, 0.0F);
  player.pos = vec2f_new(((float)winSize.width / 2) - 10, 0);
  player.size = vec2i_new(20, 13);
  player.data = SPHERE;

  bool should_run = true;
  while (should_run) {

    velocity = vec2f_addf(velocity, 0, 0.1F);

    if (player.pos.y > (float)(winSize.height - player.size.y)) {
      velocity.y = -velocity.y * 0.9F;
    }
    if (player.pos.x > (float)(winSize.width - player.size.x) ||
        player.pos.x < 0) {
      velocity.x = -velocity.x;
    }

    player.pos = vec2f_addv(player.pos, velocity);

    DisplayClear();

    DrawSprite(&player);

    // Draw velocity vector
    struct Vec2f center = vec2f_addf(player.pos, (float)player.size.x / 2,
                                     (float)player.size.y / 2);
    struct Vec2f dir = vec2f_mulf(velocity, 10, 10);
    DrawLine(center, vec2f_addv(center, dir));

    char inputStr[20];
    sprintf(inputStr, "%d", InputGetChar());
    DisplaySetStr(10, 10, inputStr);

    DisplayPresent();
  }
}
