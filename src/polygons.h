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

  CgmVec3 v1 = CgmVec3_init(15.0F, 20.0F, 0.0F);
  CgmVec3 v2 = CgmVec3_init(50.0F, 30.0F, 0.0F);

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 90.0F, 1.0F, 0.01F, 100.0F);

  CgmMat4x4 view;
  CgmVec3 cameraPos = CgmVec3_init(0.0F, 0.0F, 0.0F);

  bool persp = false;

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    // v1.x = 15.0F + sin(t) * 10.0F;
    // v1.z = 15.0F + cos(t) * 10.0F;

    CgmVec3 nv1 = CgmVec3_init_even(0);
    CgmVec3 nv2 = CgmVec3_init_even(0);

    cameraPos.z = -10.0F + (float)sin(t) * 10.0F;

    CgmMat4x4_identity(&view);
    CgmMat4x4_translate(&view, cameraPos);

    DisplayClear();

    if (persp) {
      nv1 = CgmMat4x4_mul_point(&view, v1);
      nv1 = CgmMat4x4_mul_point(&proj, nv1);

      nv2 = CgmMat4x4_mul_point(&view, v2);
      nv2 = CgmMat4x4_mul_point(&proj, nv2);

      DisplaySetStr(0, 9, "True");
    } else {
      nv1 = v1;
      nv2 = v2;
      DisplaySetStr(0, 9, "False");
    }

    DisplaySetFloat(0, 8, nv1.y);

    nv1.x = nv1.x / nv1.z;
    nv1.y = nv1.y / nv1.z;

    nv2.x = nv2.x / nv2.z;
    nv2.y = nv2.y / nv2.z;

    DrawLine(CgmVec2_init(nv1.x, nv1.y), CgmVec2_init(nv2.x, nv2.y));

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }

    if (isKeyDown('f')) {
      persp = !persp;
    }
  }
}
