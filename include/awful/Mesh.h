#ifndef MESH_H
#define MESH_H

#include <awful/Types.h>
#include <awful/libs/cgm.h>

#define MAX_VERTS 1024
#define MAX_INDEXES MAX_VERTS * 4

struct Mesh {
  // Data
  u32 count;
  CgmVec3 verts[MAX_VERTS];
  u32 indexes[MAX_INDEXES];

  // State
  CgmMat4x4 matrix;
  CgmVec3 position;
  CgmVec3 rotation;
  CgmVec3 scale;
};
typedef struct Mesh Mesh;

Mesh GenMesh();

void MeshRotate(Mesh *mesh, const CgmVec3 rotation);
void MeshSetRotation(Mesh *mesh, const CgmVec3 rotation);

void MeshUpdate(Mesh *mesh);

#endif