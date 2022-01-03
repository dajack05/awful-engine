#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Rasterizer.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  struct Sprite player;
  struct Vec2f velocity = vec2f_new(0.0F, 0.0F);
  player.pos = vec2f_new(((float)winSize.width / 2) - 3,
                         ((float)winSize.height / 2) - 2);
  player.size = vec2i_new(6, 3);
  player.data = PLAYER;

  struct Triangle tri;
  tri.p1 = vec3f_new(0, -10, 0); // Top
  tri.p2 = vec3f_new(-5, 5, 0);  // Left
  tri.p3 = vec3f_new(5, 5, 0);   // Right

  bool should_run = true;
  while (should_run) {
    pollInput();

    DisplayClear();

    DrawSprite(&player);

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }
  }
}
