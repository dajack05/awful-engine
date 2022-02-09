#include <awful/Display.h>
#include <awful/Rasterization.h>
#include <awful/Renderer.h>
#include <awful/Types.h>
#include <string.h>

float zBuffer[MAX_WIDTH * MAX_HEIGHT];

TransformedPoint transformPoint(CgmMat4x4 *model, CgmMat4x4 *view,
                                CgmMat4x4 *projection, CgmVec3 point,
                                struct WindowSize *winSize) {

  TransformedPoint r;

  CgmVec4 newPoint = CgmVec4_init(point.x, point.y, point.z, 0);

  newPoint = CgmMat4x4_mul_point4(model, newPoint);
  newPoint = CgmMat4x4_mul_point4(view, newPoint);

  const float near = 4.0F;
  const float far = 40.0F;
  r.depth = (newPoint.z - near) / far;

  newPoint = CgmMat4x4_mul_point4(projection, newPoint);

  CgmVec2 canvasPoint = CgmVec2_init(
      (int)((newPoint.x / newPoint.w + 1) * (winSize->width / 2)),
      (int)((1 - newPoint.y / newPoint.w) * (winSize->height / 2)));

  r.screenSpace = newPoint;
  r.canvasSpace = canvasPoint;

  return r;
}

void RendererSetZ(u16 x, u16 y, float depth) {
  WindowSize *size = DisplayGetSize();
  x -= 1;
  if (x > 0 && x <= size->width && y > 0 && y <= size->height) {
    int idx = x + y * size->width;
    if (depth < zBuffer[idx] || zBuffer[idx] == 0) {
      zBuffer[idx] = depth;
    }
  }
}

void RendererDrawZLine(CgmVec2 from, CgmVec2 to, float fromDepth,
                       float toDepth) {
  WindowSize *size = DisplayGetSize();
  double dx = to.x - from.x;
  double dy = to.y - from.y;

  double length = fabs(dy);
  if (fabs(dx) >= length) {
    length = fabs(dx);
  }

  dx = dx / length;
  dy = dy / length;

  double gx = fabs((toDepth - fromDepth) / length);

  double x = from.x;
  double y = from.y;
  double g = fromDepth;

  int i = 0;
  while (i < length - 1) {
    x += dx;
    y += dy;
    g += gx;

    RendererSetZ(x, y, g);

    i++;
  }
}

void DrawTriangle(CgmVec3 p1, CgmVec3 p2, CgmVec3 p3, CgmMat4x4 *model,
                  CgmMat4x4 *view, CgmMat4x4 *projection, WindowSize *winSize) {

  TransformedPoint _p1 = transformPoint(model, view, projection, p1, winSize);
  TransformedPoint _p2 = transformPoint(model, view, projection, p2, winSize);
  TransformedPoint _p3 = transformPoint(model, view, projection, p3, winSize);

  RasterDrawTri(_p1, _p2, _p3);
}

void DrawMesh(Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection) {
  WindowSize *winSize = DisplayGetSize();
  for (u16 i = 0; i < mesh->count; i += 3) {
    u16 idx1 = mesh->indexes[i + 0];
    u16 idx2 = mesh->indexes[i + 1];
    u16 idx3 = mesh->indexes[i + 2];
    DrawTriangle(mesh->verts[idx1], mesh->verts[idx2], mesh->verts[idx3],
                 &mesh->matrix, view, projection, winSize);
  }
}

#define shadesCount 9
char shades[] = ".:-=+*#%@";
void RendererPresent() {
  char *screen = DisplayGetScreen();
  WindowSize *size = DisplayGetSize();
  // Draw the buffer
  for (u32 i = 0; i < size->height * size->width; i++) {
    int x = i % size->width;
    int y = i / size->width;
    if (zBuffer[i] > 0.0F) {
      char shade = shades[shadesCount - (int)(zBuffer[i] * shadesCount)];
      screen[i] = shade;
    }
  }
}

void RendererClearZ() {
  WindowSize *size = DisplayGetSize();
  for (u32 i = 0; i < size->width * size->height; i++) {
    zBuffer[i] = 0;
  }
}