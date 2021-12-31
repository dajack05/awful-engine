#ifndef H_SPRITE
#define H_SPRITE

#include <awful/Vector.h>

struct Sprite {
  struct Vec2f pos;
  struct Vec2i size;
  const char *data;
};

#endif