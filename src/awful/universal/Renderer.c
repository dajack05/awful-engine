#include <awful/Display.h>
#include <awful/Renderer.h>

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

void DrawTriangle(CgmVec3 p1, CgmVec3 p2, CgmVec3 p3, CgmMat4x4 *model,
                  CgmMat4x4 *view, CgmMat4x4 *projection,
                  struct WindowSize *winSize) {
  CgmVec2 _p1 = transformPoint(model, view, projection, p1, winSize);
  CgmVec2 _p2 = transformPoint(model, view, projection, p2, winSize);
  CgmVec2 _p3 = transformPoint(model, view, projection, p3, winSize);

  DrawLine(_p1, _p2);
  DrawLine(_p2, _p3);
  DrawLine(_p3, _p1);
}

void DrawMesh(struct Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection,
              struct WindowSize *winSize) {
  for (u16 i = 0; i < mesh->count; i += 3) {
    u16 idx1 = mesh->indexes[i + 0];
    u16 idx2 = mesh->indexes[i + 1];
    u16 idx3 = mesh->indexes[i + 2];
    DrawTriangle(mesh->verts[idx1], mesh->verts[idx2], mesh->verts[idx3],
                 &mesh->matrix, view, projection, winSize);
  }
}