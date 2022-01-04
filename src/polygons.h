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

  struct Triangle tri1;
  tri1.p1 = vec3f_new(10, 10, 0);
  tri1.p2 = vec3f_new(20, 10, 0);
  tri1.p3 = vec3f_new(20, 20, 0);

  struct Triangle tri2;
  tri2.p1 = vec3f_new(10, 10, 0);
  tri2.p2 = vec3f_new(20, 20, 0);
  tri2.p3 = vec3f_new(10, 20, 0);

  bool should_run = true;
  while (should_run) {
    pollInput();

    if (isKeyDown('d')) {
    }

    DisplayClear();

    DrawTri(tri1);
    // DrawTri(tri2);

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }
  }
}
