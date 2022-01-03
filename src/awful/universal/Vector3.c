#include <awful/Vector.h>

#define BASIC_OP(NAME, op)                                                     \
  struct Vec3f Vec3f_##NAME##f(struct Vec3f from, float x, float y, float z) { \
    struct Vec3f v;                                                            \
    v.x = from.x op x;                                                         \
    v.y = from.y op y;                                                         \
    v.z = from.z op z;                                                         \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec3f Vec3f_##NAME##v(struct Vec3f from, struct Vec3f vec) {          \
    struct Vec3f v;                                                            \
    v.x = from.x op vec.x;                                                     \
    v.y = from.y op vec.y;                                                     \
    v.z = from.z op vec.z;                                                     \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec3i Vec3i_##NAME##f(struct Vec3i from, int x, int y, int z) {       \
    struct Vec3i v;                                                            \
    v.x = from.x op x;                                                         \
    v.y = from.y op y;                                                         \
    v.z = from.z op z;                                                         \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec3i Vec3i_##NAME##v(struct Vec3i from, struct Vec3i vec) {          \
    struct Vec3i v;                                                            \
    v.x = from.x op vec.x;                                                     \
    v.y = from.y op vec.y;                                                     \
    v.z = from.z op vec.z;                                                     \
    return v;                                                                  \
  }

struct Vec3f vec3f_new(float x, float y, float z) {
  struct Vec3f v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

struct Vec3f vec3f_clone(struct Vec3f vec) {
  struct Vec3f v;
  v.x = vec.x;
  v.y = vec.y;
  v.z = vec.z;
  return v;
}

struct Vec3i vec3i_new(int x, int y, int z) {
  struct Vec3i v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

struct Vec3i vec3i_clone(struct Vec3i vec) {
  struct Vec3i v;
  v.x = vec.x;
  v.y = vec.y;
  v.z = vec.z;
  return v;
}

BASIC_OP(add, +);
BASIC_OP(sub, -);
BASIC_OP(mul, *);
BASIC_OP(div, /);