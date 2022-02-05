#ifndef MESH_H
#define MESH_H

#include <awful/Types.h>
#include <awful/libs/cgm.h>

#define MAX_VERTS 256
#define MAX_INDEXES 256

struct Mesh {
  u16 count;
  CgmMat4x4 matrix;
  CgmVec3 verts[MAX_VERTS];
  u16 indexes[MAX_INDEXES];
};

struct Mesh GenMesh();
struct Mesh LoadOBJ(const char *path);

#endif