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

  CgmVec3 v1 = CgmVec3_init(20.0F, 20.0F, 20.0F);
  CgmVec3 v2 = CgmVec3_init(50.0F, 20.0F, 40.0F);

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 90.0F, 1.0F, 0.01F, 100.0F);

  CgmMat4x4 view;
  CgmVec3 cameraPos = CgmVec3_init(0.0F, 0.0F, 0.0F);

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    // v1.x = 15.0F + sin(t) * 10.0F;
    // v1.z = 15.0F + cos(t) * 10.0F;

    CgmVec4 nv1 = CgmVec4_init(1, 1, 1, 1);
    CgmVec4 nv2 = CgmVec4_init(1, 1, 1, 1);

    // cameraPos.z = -10.0F + (float)sin(t) * 10.0F;
    cameraPos.z += 1.0F;

    CgmMat4x4_identity(&view);
    CgmMat4x4_translate(&view, cameraPos);

    DisplayClear();

    nv1 = CgmMat4x4_mul_point4(&view, CgmVec4_init(v1.x, v1.y, v1.z, 1));
    nv1 = CgmMat4x4_mul_point4(&proj, nv1);

    nv2 = CgmMat4x4_mul_point4(&view, CgmVec4_init(v2.x, v2.y, v2.z, 1));
    nv2 = CgmMat4x4_mul_point4(&proj, nv2);

    CgmVec2 p1 =
        CgmVec2_init((int)((nv1.x / nv1.w + 1) * (winSize.width / 2)),
                     (int)((1 - nv1.y / nv1.w) * (winSize.height / 2)));

    CgmVec2 p2 =
        CgmVec2_init((int)((nv2.x / nv2.w + 1) * (winSize.width / 2)),
                     (int)((1 - nv2.y / nv2.w) * (winSize.height / 2)));

    DrawLine(p1, p2);

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }
  }
}
