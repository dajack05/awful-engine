#include <awful/Vector.h>

#define BASIC_OP(NAME, op)                                                     \
  struct Vec2f vec2f_##NAME##f(struct Vec2f from, float x, float y) {          \
    struct Vec2f v;                                                            \
    v.x = from.x op x;                                                         \
    v.y = from.y op y;                                                         \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec2f vec2f_##NAME##v(struct Vec2f from, struct Vec2f vec) {          \
    struct Vec2f v;                                                            \
    v.x = from.x op vec.x;                                                     \
    v.y = from.y op vec.y;                                                     \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec2i vec2i_##NAME##f(struct Vec2i from, int x, int y) {              \
    struct Vec2i v;                                                            \
    v.x = from.x op x;                                                         \
    v.y = from.y op y;                                                         \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  struct Vec2i vec2i_##NAME##v(struct Vec2i from, struct Vec2i vec) {          \
    struct Vec2i v;                                                            \
    v.x = from.x op vec.x;                                                     \
    v.y = from.y op vec.y;                                                     \
    return v;                                                                  \
  }

struct Vec2f vec2f_new(float x, float y) {
  struct Vec2f v;
  v.x = x;
  v.y = y;
  return v;
}

struct Vec2f vec2f_clone(struct Vec2f vec) {
  struct Vec2f v;
  v.x = vec.x;
  v.y = vec.y;
  return v;
}

struct Vec2i vec2i_new(int x, int y) {
  struct Vec2i v;
  v.x = x;
  v.y = y;
  return v;
}

struct Vec2i vec2i_clone(struct Vec2i vec) {
  struct Vec2i v;
  v.x = vec.x;
  v.y = vec.y;
  return v;
}

BASIC_OP(add, +);
BASIC_OP(sub, -);
BASIC_OP(mul, *);
BASIC_OP(div, /);