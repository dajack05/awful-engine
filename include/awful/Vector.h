#ifndef H_VECTOR
#define H_VECTOR

struct Vec2i {
  int x;
  int y;
};

struct Vec2f {
  float x;
  float y;
};

#define BASIC_OP_DEF(NAME)                                                     \
  struct Vec2f vec2f_##NAME##f(struct Vec2f from, float x, float y);           \
  struct Vec2f vec2f_##NAME##v(struct Vec2f from, struct Vec2f vec);           \
  struct Vec2i vec2i_##NAME##f(struct Vec2i from, int x, int y);               \
  struct Vec2i vec2i_##NAME##v(struct Vec2i from, struct Vec2i vec);

struct Vec2f vec2f_new(float x, float y);
struct Vec2f vec2f_clone(struct Vec2f vec);

struct Vec2i vec2i_new(int x, int y);
struct Vec2i vec2i_clone(struct Vec2i vec);

BASIC_OP_DEF(add);
BASIC_OP_DEF(sub);
BASIC_OP_DEF(mul);
BASIC_OP_DEF(div);

#endif