#include <awful/Mesh.h>

Mesh GenMesh() {
  Mesh m;

  CgmMat4x4_identity(&m.matrix);
  m.count = 0;

  m.position = CgmVec3_init_even(0);
  m.rotation = CgmVec3_init_even(0);
  m.scale = CgmVec3_init_even(1);

  return m;
}

void MeshUpdate(Mesh *mesh) {
  CgmMat4x4_identity(&mesh->matrix);

  CgmMat4x4_rotate(&mesh->matrix, CgmVec3_init(1, 0, 0), mesh->rotation.x);
  CgmMat4x4_rotate(&mesh->matrix, CgmVec3_init(0, 1, 0), mesh->rotation.y);
  CgmMat4x4_rotate(&mesh->matrix, CgmVec3_init(0, 0, 1), mesh->rotation.z);

  CgmMat4x4_scale(&mesh->matrix, mesh->scale);

  CgmMat4x4_translate(&mesh->matrix, mesh->position);
}

void MeshRotate(Mesh *mesh, const CgmVec3 rotation) {
  mesh->rotation = CgmVec3_add(mesh->rotation, rotation);
}

void MeshSetRotation(Mesh *mesh, const CgmVec3 rotation) {
  mesh->rotation = rotation;
}