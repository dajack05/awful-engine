#ifndef H_SPRITE
#define H_SPRITE

#include <awful/cgm.h>

struct Sprite {
  CgmVec2 pos;
  CgmVec2 size;
  const char *data;
};

#endif