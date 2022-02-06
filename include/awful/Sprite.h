#ifndef H_SPRITE
#define H_SPRITE

#include <awful/libs/cgm.h>

typedef struct Sprite Sprite;
struct Sprite {
  CgmVec2 pos;
  CgmVec2 size;
  const char *data;
};

#endif