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
  Mesh mesh = GenMesh();

  u16 k = 0;

  mesh.verts[k++] = CgmVec3_init(0.000000, -1.000000, 0.000000);
  mesh.verts[k++] = CgmVec3_init(0.723600, -0.447215, 0.525720);
  mesh.verts[k++] = CgmVec3_init(-0.276385, -0.447215, 0.850640);
  mesh.verts[k++] = CgmVec3_init(-0.894425, -0.447215, 0.000000);
  mesh.verts[k++] = CgmVec3_init(-0.276385, -0.447215, -0.850640);
  mesh.verts[k++] = CgmVec3_init(0.723600, -0.447215, -0.525720);
  mesh.verts[k++] = CgmVec3_init(0.276385, 0.447215, 0.850640);
  mesh.verts[k++] = CgmVec3_init(-0.723600, 0.447215, 0.525720);
  mesh.verts[k++] = CgmVec3_init(-0.723600, 0.447215, -0.525720);
  mesh.verts[k++] = CgmVec3_init(0.276385, 0.447215, -0.850640);
  mesh.verts[k++] = CgmVec3_init(0.894425, 0.447215, 0.000000);
  mesh.verts[k++] = CgmVec3_init(0.000000, 1.000000, 0.000000);

  k = 0;
  mesh.indexes[k++] = 1 - 1;
  mesh.indexes[k++] = 2 - 1;
  mesh.indexes[k++] = 3 - 1;
  mesh.indexes[k++] = 2 - 1;
  mesh.indexes[k++] = 1 - 1;
  mesh.indexes[k++] = 6 - 1;
  mesh.indexes[k++] = 1 - 1;
  mesh.indexes[k++] = 3 - 1;
  mesh.indexes[k++] = 4 - 1;
  mesh.indexes[k++] = 1 - 1;
  mesh.indexes[k++] = 4 - 1;
  mesh.indexes[k++] = 5 - 1;
  mesh.indexes[k++] = 1 - 1;
  mesh.indexes[k++] = 5 - 1;
  mesh.indexes[k++] = 6 - 1;
  mesh.indexes[k++] = 2 - 1;
  mesh.indexes[k++] = 6 - 1;
  mesh.indexes[k++] = 11 - 1;
  mesh.indexes[k++] = 3 - 1;
  mesh.indexes[k++] = 2 - 1;
  mesh.indexes[k++] = 7 - 1;
  mesh.indexes[k++] = 4 - 1;
  mesh.indexes[k++] = 3 - 1;
  mesh.indexes[k++] = 8 - 1;
  mesh.indexes[k++] = 5 - 1;
  mesh.indexes[k++] = 4 - 1;
  mesh.indexes[k++] = 9 - 1;
  mesh.indexes[k++] = 6 - 1;
  mesh.indexes[k++] = 5 - 1;
  mesh.indexes[k++] = 10 - 1;
  mesh.indexes[k++] = 2 - 1;
  mesh.indexes[k++] = 11 - 1;
  mesh.indexes[k++] = 7 - 1;
  mesh.indexes[k++] = 3 - 1;
  mesh.indexes[k++] = 7 - 1;
  mesh.indexes[k++] = 8 - 1;
  mesh.indexes[k++] = 4 - 1;
  mesh.indexes[k++] = 8 - 1;
  mesh.indexes[k++] = 9 - 1;
  mesh.indexes[k++] = 5 - 1;
  mesh.indexes[k++] = 9 - 1;
  mesh.indexes[k++] = 10 - 1;
  mesh.indexes[k++] = 6 - 1;
  mesh.indexes[k++] = 10 - 1;
  mesh.indexes[k++] = 11 - 1;
  mesh.indexes[k++] = 7 - 1;
  mesh.indexes[k++] = 11 - 1;
  mesh.indexes[k++] = 12 - 1;
  mesh.indexes[k++] = 8 - 1;
  mesh.indexes[k++] = 7 - 1;
  mesh.indexes[k++] = 12 - 1;
  mesh.indexes[k++] = 9 - 1;
  mesh.indexes[k++] = 8 - 1;
  mesh.indexes[k++] = 12 - 1;
  mesh.indexes[k++] = 10 - 1;
  mesh.indexes[k++] = 9 - 1;
  mesh.indexes[k++] = 12 - 1;
  mesh.indexes[k++] = 11 - 1;
  mesh.indexes[k++] = 10 - 1;
  mesh.indexes[k++] = 12 - 1;

  // u16 k = 0;
  // mesh.verts[k++] = CgmVec3_init(-1.0F, -1.0F, 1.0F);
  // mesh.verts[k++] = CgmVec3_init(-1.0F, 1.0F, 1.0F);
  // mesh.verts[k++] = CgmVec3_init(-1.0F, -1.0F, -1.0F);
  // mesh.verts[k++] = CgmVec3_init(-1.0F, 1.0F, -1.0F);
  // mesh.verts[k++] = CgmVec3_init(1.0F, -1.0F, 1.0F);
  // mesh.verts[k++] = CgmVec3_init(1.0F, 1.0F, 1.0F);
  // mesh.verts[k++] = CgmVec3_init(1.0F, -1.0F, -1.0F);
  // mesh.verts[k++] = CgmVec3_init(1.0F, 1.0F, -1.0F);

  // k = 0;
  // mesh.indexes[k++] = 2 - 1;
  // mesh.indexes[k++] = 3 - 1;
  // mesh.indexes[k++] = 1 - 1;
  // mesh.indexes[k++] = 4 - 1;
  // mesh.indexes[k++] = 7 - 1;
  // mesh.indexes[k++] = 3 - 1;
  // mesh.indexes[k++] = 8 - 1;
  // mesh.indexes[k++] = 5 - 1;
  // mesh.indexes[k++] = 7 - 1;
  // mesh.indexes[k++] = 6 - 1;
  // mesh.indexes[k++] = 1 - 1;
  // mesh.indexes[k++] = 5 - 1;
  // mesh.indexes[k++] = 7 - 1;
  // mesh.indexes[k++] = 1 - 1;
  // mesh.indexes[k++] = 3 - 1;
  // mesh.indexes[k++] = 4 - 1;
  // mesh.indexes[k++] = 6 - 1;
  // mesh.indexes[k++] = 8 - 1;
  // mesh.indexes[k++] = 2 - 1;
  // mesh.indexes[k++] = 4 - 1;
  // mesh.indexes[k++] = 3 - 1;
  // mesh.indexes[k++] = 4 - 1;
  // mesh.indexes[k++] = 8 - 1;
  // mesh.indexes[k++] = 7 - 1;
  // mesh.indexes[k++] = 8 - 1;
  // mesh.indexes[k++] = 6 - 1;
  // mesh.indexes[k++] = 5 - 1;
  // mesh.indexes[k++] = 6 - 1;
  // mesh.indexes[k++] = 2 - 1;
  // mesh.indexes[k++] = 1 - 1;
  // mesh.indexes[k++] = 7 - 1;
  // mesh.indexes[k++] = 5 - 1;
  // mesh.indexes[k++] = 1 - 1;
  // mesh.indexes[k++] = 4 - 1;
  // mesh.indexes[k++] = 2 - 1;
  // mesh.indexes[k++] = 6 - 1;

  mesh.count = k;

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
