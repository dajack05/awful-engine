#ifndef RENDERER_H
#define RENDERER_H

#include <awful/Display.h>
#include <awful/Mesh.h>

void DrawMesh(Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection);
void RendererClearZ();
void RendererPresent();

void RendererDrawZLine(CgmVec2 from, CgmVec2 to, float fromDepth, float toDepth);

#endif