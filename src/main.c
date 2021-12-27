#include <Global.h>

#include "assets.h"

#include <Display.h>
#include <System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_HEIGHT 50
#define SCREEN_WIDTH (SCREEN_HEIGHT * 2)

void sleepUntilFPS(u16 targetFPS, u64 startTime) {
  u64 now = SystemTime();
  double timePerFrame = 1000.0 / targetFPS;
  while ((double)(now - startTime) <= timePerFrame) {
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

  float shapeVelX = 0.2F;
  float shapeVelY = 0.2F;
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
    double t = (double)startTime / 1000.0F;

    DisplayClear();

    // Update
    player.x = (int)((SCREEN_WIDTH / 2.0) - (player.w / 2) +
                     cos(t) * (SCREEN_WIDTH / 3.0));
    player.y = SCREEN_HEIGHT - player.h - fabs(sin(t) * (SCREEN_HEIGHT / 2.0));

    // Plane Movement
    if (planeFacingRight) {
      plane.x += 1.0;
    } else {
      plane.x -= 1.0;
    }

    plane.y = (int)(5.0 - sin(t / 2.0) * 5.0);

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
    DrawSprite(&shape);

    DrawLine(plane.x + (plane.w / 2), plane.y + 3, player.x + player.w / 2,
             player.y + 1);

    DrawSprite(&player);
    DrawSprite(&plane);

    DisplayPresent();
    frame++;
    sleepUntilFPS(10, startTime);
  }

  return 0;
}
