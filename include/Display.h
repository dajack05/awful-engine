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

void DisplayClear();

void DrawSprite(struct Sprite *sprite);

void DrawLine(s8 from_x, s8 from_y, s8 to_x, s8 to_y);

#endif