#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Matrix.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  struct Vec3f v1 = vec3f_new(15.0F, 10.0F, 0.0F);
  struct Vec3f v2 = vec3f_new(50.0F, 20.0F, 0.0F);

  struct Matrix proj = createProjection(45.0F, 1.0F, 0.01F, 100.0F);

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    v1.x = 15.0F + sin(t) * 10.0F;

    struct Vec3f nv1 = vec3f_mulm(v1,proj);

    DisplayClear();

    DrawLine(v1, v2);

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }
  }
}
