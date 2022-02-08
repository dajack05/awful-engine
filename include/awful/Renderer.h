#ifndef RENDERER_H
#define RENDERER_H

#include <awful/Display.h>
#include <awful/Mesh.h>

typedef union TransformedPoint TransformedPoint;
union TransformedPoint {
  struct {
    CgmVec4 screenSpace;
    CgmVec2 canvasSpace;
    float depth;
  };
  float a[7];
};

void DrawMesh(Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection);
void RendererClearZ();
void RendererPresent();

void RendererDrawZLine(CgmVec2 from, CgmVec2 to, float fromDepth, float toDepth);
void RendererSetZ(u16 x, u16 y, float depth);

#endif