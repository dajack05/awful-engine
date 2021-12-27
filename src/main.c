#include <Global.h>

#include "assets.h"

#include <Display.h>
#include <System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH (SCREEN_HEIGHT * 2)

void sleepUntilFPS(u16 targetFPS, u64 startTime) {
  u64 now = SystemTime();
  u64 timePerFrame = 1000 / targetFPS;
  while (now - startTime <= timePerFrame) {
    now = SystemTime();
  }
}

int main(int argc, char **argv) {

  printf("Current OS: %s\n", OS);

  DisplayInit(SCREEN_WIDTH, SCREEN_HEIGHT, false);

  DisplaySetChar(1, 1, ' ');

  struct Sprite player;
  player.x = 0;
  player.y = 0;
  player.w = 20;
  player.h = 13;
  player.data = SPHERE;

  bool planeFacingRight = true;
  struct Sprite plane;
  plane.x = 0;
  plane.y = 0;
  plane.w = 16;
  plane.h = 4;
  plane.data = PLANE_RIGHT;

  int shapeVelX = 1;
  int shapeVelY = 1;
  struct Sprite shape;
  shape.x = 0;
  shape.y = 0;
  shape.w = 33;
  shape.h = 18;
  shape.data = SHAPE;

  bool should_run = true;
  u32 frame = 0;
  while (should_run) {
    u64 startTime = SystemTime();

    DisplayClear();

    // Update
    player.x = (SCREEN_WIDTH / 2) - (player.w / 2) + cos(startTime) * 7;
    player.y = SCREEN_HEIGHT - player.h - fabs(sin(startTime) * 12);

    // Plane Movement
    if (planeFacingRight) {
      plane.x += 2;
    } else {
      plane.x -= 2;
    }

    plane.y = 2 - sin(startTime / 4) * 2;

    // Plane Logic
    if (plane.x >= SCREEN_WIDTH - plane.w) {
      planeFacingRight = false;
      plane.data = PLANE_LEFT;
    } else if (plane.x <= 0) {
      planeFacingRight = true;
      plane.data = PLANE_RIGHT;
    }

    // Shape Movement
    shape.x += shapeVelX;
    shape.y += shapeVelY;

    // Shape Logic
    if (shape.x >= SCREEN_WIDTH - shape.w || shape.x < 0) {
      shapeVelX *= -1;
    }
    if (shape.y >= SCREEN_HEIGHT - shape.h || shape.y < 0) {
      shapeVelY *= -1;
    }

    // Draw
    DisplayDrawSprite(&shape);
    DisplayDrawSprite(&player);
    DisplayDrawSprite(&plane);

    DisplayPresent();
    frame++;
    sleepUntilFPS(10, startTime);
  }

  return 0;
}
