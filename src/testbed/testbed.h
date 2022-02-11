#include "assets.h"

#include <awful/Display.h>
#include <awful/Input.h>
#include <awful/Loaders.h>
#include <awful/Mesh.h>
#include <awful/Renderer.h>
#include <awful/Sprite.h>
#include <awful/System.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Run() {

  DisplayInit();
  WindowSize *winSize = DisplayGetSize();

  // Front Face
  Mesh mesh = LoadOBJ("./assets/spyro.obj");
  mesh.scale = CgmVec3_init_even(3);
  mesh.position = CgmVec3_init(0, 4, 0);

  Mesh map = LoadOBJ("./assets/map.obj");
  map.scale = CgmVec3_init_even(1);
  map.position = CgmVec3_init(0, 0, 0);

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 45.0F,
                        (float)winSize->width / 2 / (float)winSize->height,
                        0.1F, 50.0F);

  CgmMat4x4 view;
  CgmMat4x4_identity(&view);
  CgmMat4x4_translate(&view, CgmVec3_init(0, 0, 20));

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    MeshRotate(&mesh, CgmVec3_init(0, 0.05, 0));

    RendererClearZ();
    DisplayClear();

    // MeshUpdate(&mesh);
    // DrawMesh(&mesh, &view, &proj);

    MeshUpdate(&map);
    DrawMesh(&map, &view, &proj);

    RendererPresent();

    DisplayPresent();

    if (isKeyDown(27)) {
      should_run = false;
      DisplayClear();
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

    if (isKeyDown('i')) {
      CgmMat4x4_rotate(&view, CgmVec3_init(1, 0, 0), -0.1);
    }
    if (isKeyDown('k')) {
      CgmMat4x4_rotate(&view, CgmVec3_init(1, 0, 0), 0.1);
    }
    if (isKeyDown('j')) {
      CgmMat4x4_rotate(&view, CgmVec3_init(0, 1, 0), 0.1);
    }
    if (isKeyDown('l')) {
      CgmMat4x4_rotate(&view, CgmVec3_init(0, 1, 0), -0.1);
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
