#include <awful/Rasterization.h>

/*

An implimentation of the Barycentric algorithm.

Keeps it simple, and is integer based.

*/

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

float InterpolatedDepth(TransformedPoint p1, TransformedPoint p2,
                        TransformedPoint p3, float x, float y) {

  float a = cgm_lerp(p1.depth, p2.depth, x);
  float b = cgm_lerp(p2.depth, p3.depth, y);
  float c = cgm_lerp(a, b, y);

  return p1.depth;
}

void RasterDrawTri(TransformedPoint p1, TransformedPoint p2,
                   TransformedPoint p3) {
  // Generate Bounding Box
  int maxx = max(p1.canvasSpace.x, max(p2.canvasSpace.x, p3.canvasSpace.x));
  int minx = min(p1.canvasSpace.x, min(p2.canvasSpace.x, p3.canvasSpace.x));
  int maxy = max(p1.canvasSpace.y, max(p2.canvasSpace.y, p3.canvasSpace.y));
  int miny = min(p1.canvasSpace.y, min(p2.canvasSpace.y, p3.canvasSpace.y));

  float maxDist = CgmVec2_len(
      CgmVec2_sub(CgmVec2_init(maxx, maxy), CgmVec2_init(minx, miny)));

  // Distance between p1 and p2
  CgmVec2 vs1 = CgmVec2_init(p2.canvasSpace.x - p1.canvasSpace.x,
                             p2.canvasSpace.y - p1.canvasSpace.y);
  // Distance between p1 and p3
  CgmVec2 vs2 = CgmVec2_init(p3.canvasSpace.x - p1.canvasSpace.x,
                             p3.canvasSpace.y - p1.canvasSpace.y);

  // Go point-by-point and test if it's within the triangle
  for (int x = minx; x < maxx; x++) {
    for (int y = miny; y < maxy; y++) {
      CgmVec2 testPoint =
          CgmVec2_init(x - p1.canvasSpace.x, y - p1.canvasSpace.y);

      float crossVs1Vs2 = CgmVec2_mul_cross_vec(vs1, vs2);

      float s = CgmVec2_mul_cross_vec(testPoint, vs2) / crossVs1Vs2;
      float t = CgmVec2_mul_cross_vec(vs1, testPoint) / crossVs1Vs2;

      if ((s >= 0) && (t >= 0) && (s + t <= 1)) {
        // Find the depth for our given point
        float d = InterpolatedDepth(p1, p2, p3, s / maxDist, t / maxDist);

        RendererSetZ(x, y, d);
      }
    }
  }
}