#include <awful/Rasterizer.h>

#include <awful/Display.h>
#include <limits.h>

float min(float a, float b) {
  if (a < b) {
    return a;
  }
  return b;
}

float max(float a, float b) {
  if (a > b) {
    return a;
  }
  return b;
}

void fillBottomFlatTriangle3D(struct Vec3f v1, struct Vec3f v2,
                              struct Vec3f v3) {
  float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
  float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

  float curx1 = v1.x;
  float curx2 = v1.x;

  float curz1 = v1.z;
  float curz2 = v1.z;

  for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {
    // Ok... We gotta figure out how to lerp the Z value
    float lineStartZ = 0.0F;
    float lineEndZ = 1.0F;
    DrawLine3D(vec3f_new(curx1, scanlineY, lineStartZ),
               vec3f_new(curx2, scanlineY, lineEndZ));
    curx1 += invslope1;
    curx2 += invslope2;
  }
}

void fillTopFlatTriangle3D(struct Vec3f v1, struct Vec3f v2, struct Vec3f v3) {
  float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
  float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

  float curx1 = v3.x;
  float curx2 = v3.x;

  for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {
    // Ok... We gotta figure out how to lerp the Z value
    float lineStartZ = 0.0F;
    float lineEndZ = 1.0F;
    DrawLine3D(vec3f_new(curx1, scanlineY, lineStartZ),
               vec3f_new(curx2, scanlineY, lineEndZ));
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

void fillBottomFlatTriangle2D(struct Vec3f v1, struct Vec3f v2,
                              struct Vec3f v3) {
  float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
  float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

  float curx1 = v1.x;
  float curx2 = v1.x;

  for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {
    DrawLine(vec2f_new(curx1, scanlineY), vec2f_new(curx2, scanlineY));
    curx1 += invslope1;
    curx2 += invslope2;
  }
}

void fillTopFlatTriangle2D(struct Vec3f v1, struct Vec3f v2, struct Vec3f v3) {
  float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
  float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

  float curx1 = v3.x;
  float curx2 = v3.x;

  for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {
    DrawLine(vec2f_new(curx1, scanlineY), vec2f_new(curx2, scanlineY));
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

struct Vec3f *minYVec(struct Vec3f *a, struct Vec3f *b) {
  if (a->y < b->y) {
    return a;
  }
  return b;
}

struct Triangle sortVerticesAscendingByY(struct Triangle tri) {
  struct Triangle triangle;
  struct Vec3f values[3];
  values[0] = tri.p1;
  values[1] = tri.p2;
  values[2] = tri.p3;

  struct Vec3f *currentVec;
  currentVec = minYVec(minYVec(&tri.p1, &tri.p2), &tri.p3);
  triangle.p1 = vec3f_clone(*currentVec);
  currentVec->x = __FLT_MAX__;
  currentVec->y = __FLT_MAX__;

  currentVec = minYVec(minYVec(&tri.p1, &tri.p2), &tri.p3);
  triangle.p2 = vec3f_clone(*currentVec);
  currentVec->x = __FLT_MAX__;
  currentVec->y = __FLT_MAX__;

  currentVec = minYVec(minYVec(&tri.p1, &tri.p2), &tri.p3);
  triangle.p3 = vec3f_clone(*currentVec);
  currentVec->x = __FLT_MAX__;
  currentVec->y = __FLT_MAX__;

  return triangle;
}

void DrawTri(struct Triangle tri) {
  struct Triangle mTri = sortVerticesAscendingByY(tri);

  if (mTri.p2.y == mTri.p3.y) {
    fillBottomFlatTriangle3D(mTri.p1, mTri.p2, mTri.p3);
  }
  /* check for trivial case of top-flat triangle */
  else if (mTri.p1.y == mTri.p2.y) {
    fillTopFlatTriangle3D(mTri.p1, mTri.p2, mTri.p3);
  } else {
    /* general case - split the triangle in a topflat and bottom-flat one */
    struct Vec2f v4 =
        vec2f_new((int)(mTri.p1.x + ((float)(mTri.p2.y - mTri.p1.y) /
                                     (float)(mTri.p3.y - mTri.p1.y)) *
                                        (mTri.p3.x - mTri.p1.x)),
                  mTri.p2.y);
    fillBottomFlatTriangle3D(mTri.p1, mTri.p2, mTri.p3);
    fillTopFlatTriangle3D(mTri.p2, mTri.p3, mTri.p1);
  }
}