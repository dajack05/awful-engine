#include <awful/Awful.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Sprite s;

void DrawControls() { DrawSprite(&s); }

void Run(char *path) {

  struct WindowSize winSize = DisplayInit(false);

  s.pos = CgmVec2_init(1, 1);
  s.data = " --[ Controls ]-- "
           "|    MOVEMENT    |"
           "|  Forward - W   |"
           "| Backward - S   |"
           "|     Left - A   |"
           "|    Right - D   |"
           "|       Up - E   |"
           "|     Down - Q   |"
           " ---------------- "
           "|      MISC.     |"
           "| Quit - Esc     |"
           " ---------------- ";
  s.size = CgmVec2_init(18, 12);

  // Front Face
  Mesh mesh = LoadOBJ(path);
  mesh.scale = CgmVec3_init_even(3);

  CgmMat4x4 proj;
  CgmMat4x4_perspective(&proj, 45.0F,
                        (float)winSize.width / 2 / (float)winSize.height, 0.1F,
                        50.0F);

  CgmMat4x4 view;
  CgmMat4x4_identity(&view);
  CgmMat4x4_translate(&view, CgmVec3_init(0, 0, 20));

  bool should_run = true;
  double t = 0.0;
  while (should_run) {
    pollInput();
    t += 0.1;

    MeshRotate(&mesh, CgmVec3_init(0, 0.05, 0));

    DisplayClear();

    mesh.position = CgmVec3_init(0, 2, 0);
    MeshUpdate(&mesh);
    DrawMesh(&mesh, &view, &proj, &winSize);

    DrawControls();

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
    if (isKeyDown('q')) {
      moveVec.y = -1;
    }
    if (isKeyDown('e')) {
      moveVec.y = 1;
    }

    CgmMat4x4_translate(&view, moveVec);
  }
}
