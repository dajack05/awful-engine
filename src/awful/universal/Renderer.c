#include <awful/Display.h>
#include <awful/Renderer.h>

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

void DrawTriangle(CgmVec3 p1, CgmVec3 p2, CgmVec3 p3, CgmMat4x4 *model,
                  CgmMat4x4 *view, CgmMat4x4 *projection,
                  struct WindowSize *winSize) {
  TransformedPoint _p1 = transformPoint(model, view, projection, p1, winSize);
  TransformedPoint _p2 = transformPoint(model, view, projection, p2, winSize);
  TransformedPoint _p3 = transformPoint(model, view, projection, p3, winSize);

  DrawGradientLine(_p1.canvasSpace, _p2.canvasSpace, _p1.depth, _p2.depth);
  DrawGradientLine(_p2.canvasSpace, _p3.canvasSpace, _p2.depth, _p3.depth);
  DrawGradientLine(_p3.canvasSpace, _p1.canvasSpace, _p3.depth, _p1.depth);
}

void DrawMesh(Mesh *mesh, CgmMat4x4 *view, CgmMat4x4 *projection,
              struct WindowSize *winSize) {
  for (u16 i = 0; i < mesh->count; i += 3) {
    u16 idx1 = mesh->indexes[i + 0];
    u16 idx2 = mesh->indexes[i + 1];
    u16 idx3 = mesh->indexes[i + 2];
    DrawTriangle(mesh->verts[idx1], mesh->verts[idx2], mesh->verts[idx3],
                 &mesh->matrix, view, projection, winSize);
  }
}