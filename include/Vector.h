#ifndef H_VECTOR
#define H_VECTOR

struct Vector {
  float x;
  float y;
};

#define BASIC_OP_F(NAME, op)                                                   \
  struct Vector vec_##NAME##f(struct Vector from, float x, float y) {          \
    struct Vector v;                                                           \
    v.x = from.x op x;                                                         \
    v.y = from.y op y;                                                         \
    return v;                                                                  \
  }

#define BASIC_OP_V(NAME, op)                                                   \
  struct Vector vec_##NAME##v(struct Vector from, struct Vector vec) {         \
    struct Vector v;                                                           \
    v.x = from.x op vec.x;                                                     \
    v.y = from.y op vec.y;                                                     \
    return v;                                                                  \
  }

struct Vector vec_new(float x, float y) {
  struct Vector v;
  v.x = x;
  v.y = y;
  return v;
}

struct Vector vec_clone(struct Vector vec) {
  struct Vector v;
  v.x = vec.x;
  v.y = vec.y;
  return v;
}

BASIC_OP_V(add, +);
BASIC_OP_F(add, +);

BASIC_OP_V(sub, -);
BASIC_OP_F(sub, -);

#endif