#ifndef H_DISPLAY
#define H_DISPLAY

#include <Global.h>
#include <Sprite.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50

void DisplayInit(u8 width, u8 height, bool wide);
void DisplayPresent();

void DisplaySetChar(u8 x, u8 y, char c);
void DisplaySetStr(u8 x, u8 y, const char *str);

void DisplayDrawSprite(struct Sprite *sprite);

void DisplayClear();

#endif