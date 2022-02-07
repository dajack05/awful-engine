#include <awful/Display.h>
#include <awful/Renderer.h>

u16 zBuffer[MAX_WIDTH * MAX_HEIGHT];

// Helper for matrix stuff
typedef union TransformedPoint TransformedPoint;
union TransformedPoint {
  struct {
    CgmVec4 screenSpace;
    CgmVec2 canvasSpace;
    float depth;
  };
  float a[7];
};

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

void DrawZLine(CgmVec2 from, CgmVec2 to, float fromDepth, float toDepth) {
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

    zBuffer[(int)(x + y * MAX_WIDTH)] = g * 9;

    i++;
  }
}

void DrawTriangle(CgmVec3 p1, CgmVec3 p2, CgmVec3 p3, CgmMat4x4 *model,
                  CgmMat4x4 *view, CgmMat4x4 *projection, WindowSize *winSize) {

  TransformedPoint _p1 = transformPoint(model, view, projection, p1, winSize);
  TransformedPoint _p2 = transformPoint(model, view, projection, p2, winSize);
  TransformedPoint _p3 = transformPoint(model, view, projection, p3, winSize);

  DrawZLine(_p1.canvasSpace, _p2.canvasSpace, _p1.depth, _p2.depth);
  DrawZLine(_p2.canvasSpace, _p3.canvasSpace, _p2.depth, _p3.depth);
  DrawZLine(_p3.canvasSpace, _p1.canvasSpace, _p3.depth, _p1.depth);
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

void RendererPresent() {
  char *screen = DisplayGetScreen();
  // Draw the buffer
  for (u32 i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++) {
    screen[i] = '0' + zBuffer[i];
  }
}

void RendererClearZ() {
  for (u32 i = 0; i < MAX_WIDTH * MAX_HEIGHT; i++) {
    zBuffer[i] = 0;
  }
}