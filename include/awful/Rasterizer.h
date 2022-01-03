/**
 *
 * 1/3/222
 * Rasterizer.h
 * Daniel J
 *
 * Rasterizer.h
 *
 **/

#ifndef H_RASTERIZER
#define H_RASTERIZER

#include <awful/Vector.h>

struct Triangle {
  struct Vec3f p1;
  struct Vec3f p2;
  struct Vec3f p3;
};

void DrawTri(struct Triangle *tri);

#endif