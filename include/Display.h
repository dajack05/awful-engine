#ifndef H_DISPLAY
#define H_DISPLAY

/*

   DisplayInit: Create and show terminal and return proper size
DisplayPresent: Update the terminal with the correct data
DisplaySetChar: Set a char at a given coordinate
 DisplaySetStr: Set a string starting at a given coordinate
  DisplayClear: Clear the terminal (still requires DisplayPresent to be called)
    DrawSprite: Draw a Sprite at a given location
      DrawLine: Draw a line from x0,y0 to x1,y1

*/

#include <Global.h>
#include <Sprite.h>

#define MAX_WIDTH 50
#define MAX_HEIGHT 50

struct WindowSize {
  u16 width;
  u16 height;
};

/**
 * Sets up the terminal and returns the size of the terminal
 */
struct WindowSize DisplayInit(bool wide);
void DisplayPresent();

void DisplaySetChar(u16 x, u16 y, char c);
void DisplaySetStr(u16 x, u16 y, const char *str);

void DisplayClear();

void DrawSprite(struct Sprite *sprite);

void DrawLine(s16 from_x, s16 from_y, s16 to_x, s16 to_y);

#endif