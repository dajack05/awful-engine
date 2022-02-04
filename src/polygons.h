#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CgmVec2 transformPoint(CgmMat4x4 *model, CgmMat4x4 *view, CgmMat4x4 *projection,
                       CgmVec3 point, struct WindowSize *winSize) {
  CgmVec4 newPoint = CgmVec4_init(point.x, point.y, point.z, 0);

  newPoint = CgmMat4x4_mul_point4(model, newPoint);
  newPoint = CgmMat4x4_mul_point4(view, newPoint);
  newPoint = CgmMat4x4_mul_point4(projection, newPoint);

  return CgmVec2_init(
      (int)((newPoint.x / newPoint.w + 1) * (winSize->width / 2)),
      (int)((1 - newPoint.y / newPoint.w) * (winSize->height / 2)));
}

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  // Front Face
  CgmVec3 v11 = CgmVec3_init(-05, -05, -05);
  CgmVec3 v12 = CgmVec3_init(+05, -05, -05);
  CgmVec3 v13 = CgmVec3_init(+05, +05, -05);
  CgmVec3 v14 = CgmVec3_init(-05, +05, -05);

  CgmVec3 v21 = CgmVec3_init(-05, -05, +05);
  CgmVec3 v22 = CgmVec3_init(+05, -05, +05);
  CgmVec3 v23 = CgmVec3_init(+05, +05, +05);
  CgmVec3 v24 = CgmVec3_init(-05, +05, +05);

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 45.0F,
                        (float)winSize.width / 2 / (float)winSize.height, 0.01F,
                        100.0F);

  CgmMat4x4 view;
  CgmMat4x4_identity(&view);
  CgmMat4x4_translate(&view, CgmVec3_init(0, 0, 20));

  CgmMat4x4 model;
  CgmMat4x4_identity(&model);

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    // CgmMat4x4_translate(&model, CgmVec3_init(0.0F, 0.0F, 0.2F));
    CgmMat4x4_rotate(&model, CgmVec3_init(0, 1, 0), 0.1F);

    // Transform Points
    CgmVec2 p11 = transformPoint(&model, &view, &proj, v11, &winSize);
    CgmVec2 p12 = transformPoint(&model, &view, &proj, v12, &winSize);
    CgmVec2 p13 = transformPoint(&model, &view, &proj, v13, &winSize);
    CgmVec2 p14 = transformPoint(&model, &view, &proj, v14, &winSize);

    CgmVec2 p21 = transformPoint(&model, &view, &proj, v21, &winSize);
    CgmVec2 p22 = transformPoint(&model, &view, &proj, v22, &winSize);
    CgmVec2 p23 = transformPoint(&model, &view, &proj, v23, &winSize);
    CgmVec2 p24 = transformPoint(&model, &view, &proj, v24, &winSize);

    DisplayClear();

    DrawLine(p11, p12);
    DrawLine(p12, p13);
    DrawLine(p13, p14);
    DrawLine(p14, p11);

    DrawLine(p21, p22);
    DrawLine(p22, p23);
    DrawLine(p23, p24);
    DrawLine(p24, p21);

    DrawLine(p11, p21);
    DrawLine(p12, p22);
    DrawLine(p13, p23);
    DrawLine(p14, p24);

    DisplayPresent();

    if (isKeyDown('q')) {
      should_run = false;
    }
  }
}
