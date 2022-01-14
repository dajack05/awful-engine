#ifndef H_VECTOR
#define H_VECTOR

#include <awful/Matrix.h>

struct Vec2i {
  int x;
  int y;
};

struct Vec2f {
  float x;
  float y;
};

struct Vec3i {
  int x;
  int y;
  int z;
};

struct Vec3f {
  float x;
  float y;
  float z;
};

#define BASIC_OP_DEF(NAME)                                                     \
  struct Vec2f vec2f_##NAME##f(struct Vec2f from, float x, float y);           \
  struct Vec2f vec2f_##NAME##v(struct Vec2f from, struct Vec2f vec);           \
  struct Vec2i vec2i_##NAME##f(struct Vec2i from, int x, int y);               \
  struct Vec2i vec2i_##NAME##v(struct Vec2i from, struct Vec2i vec);           \
                                                                               \
  struct Vec3f vec3f_##NAME##f(struct Vec3f from, float x, float y, float z);  \
  struct Vec3f vec3f_##NAME##v(struct Vec3f from, struct Vec3f vec);           \
  struct Vec3i vec3i_##NAME##f(struct Vec3i from, int x, int y, int z);        \
  struct Vec3i vec3i_##NAME##v(struct Vec3i from, struct Vec3i vec);

struct Vec2f vec2f_new(float x, float y);
struct Vec2f vec2f_clone(struct Vec2f vec);

struct Vec2i vec2i_new(int x, int y);
struct Vec2i vec2i_clone(struct Vec2i vec);

struct Vec3f vec3f_new(float x, float y, float z);
struct Vec3f vec3f_clone(struct Vec3f vec);

struct Vec3i vec3i_new(int x, int y, int z);
struct Vec3i vec3i_clone(struct Vec3i vec);

BASIC_OP_DEF(add);
BASIC_OP_DEF(sub);
BASIC_OP_DEF(mul);
BASIC_OP_DEF(div);

struct Vec3f vec3f_mulm(struct Vec3f vec, struct Matrix mat);

#endif