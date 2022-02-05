#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Mesh.h>
#include <awful/Renderer.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Run() {

  struct WindowSize winSize = DisplayInit(false);

  // Front Face
  struct Mesh mesh = LoadOBJ("./dev/cube.obj");

  CgmMat4x4_scale(&mesh.matrix, CgmVec3_init(4, 4, 4));

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 45.0F,
                        (float)winSize.width / 2 / (float)winSize.height, 0.01F,
                        100.0F);

  CgmMat4x4 view;
  CgmMat4x4_identity(&view);
  CgmMat4x4_translate(&view, CgmVec3_init(0, 0, 20));

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    // CgmMat4x4_translate(&model, CgmVec3_init(0.0F, 0.0F, 0.2F));
    CgmMat4x4_rotate(&mesh.matrix, CgmVec3_init(0, 1, 0), 0.1F);

    DisplayClear();

    DrawMesh(&mesh, &view, &proj, &winSize);

    DisplayPresent();

    if (isKeyDown('t')) {
      should_run = false;
    }

    CgmVec3 moveVec = CgmVec3_init(0, 0, 0);

    if (isKeyDown('w')) {
      moveVec.z = -1;
    }
    if (isKeyDown('s')) {
      moveVec.z = 1;
    }
    if (isKeyDown('a')) {
      moveVec.x = -1;
    }
    if (isKeyDown('d')) {
      moveVec.x = 1;
    }
    if (isKeyDown('q')) {
      moveVec.y = -1;
    }
    if (isKeyDown('e')) {
      moveVec.y = 1;
    }

    CgmMat4x4_translate(&view, moveVec);
  }
}
