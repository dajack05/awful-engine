#ifndef RENDERER_H
#define RENDERER_H

#include <awful/Display.h>
#include <awful/Mesh.h>

void DrawMesh(struct Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection,
              struct WindowSize *winSize);

#endif