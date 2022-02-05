#ifndef MESH_H
#define MESH_H

#include <awful/Types.h>
#include <awful/libs/cgm.h>

#define MAX_VERTS 512
#define MAX_INDEXES 4096

struct Mesh {
  u32 count;
  CgmMat4x4 matrix;
  CgmVec3 verts[MAX_VERTS];
  u32 indexes[MAX_INDEXES];
};

struct Mesh GenMesh();
struct Mesh LoadOBJ(const char *path);

#endif