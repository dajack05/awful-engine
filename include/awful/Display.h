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

#include <awful/Types.h>
#include <awful/libs/cgm.h>

#define MAX_WIDTH 200
#define MAX_HEIGHT 200
#define TARGET_FPS 30

struct Sprite;

typedef struct WindowSize WindowSize;
struct WindowSize {
  u16 width;
  u16 height;
};

void DisplayInit();

void DisplayPresent();

void DisplaySetChar(u16 x, u16 y, char c);
void DisplaySetStr(u16 x, u16 y, const char *str);
void DisplaySetInt(u16 x, u16 y, const int value);
void DisplaySetFloat(u16 x, u16 y, const float value);

void DisplayClear();

void DrawSprite(struct Sprite *sprite);

void DrawLine(CgmVec2 from, CgmVec2 to);
void DrawGradientLine(CgmVec2 from, CgmVec2 to, float fromDepth, float toDepth);

void DisplaySetIsWide(bool wide);
void SetSize(WindowSize size);
WindowSize *DisplayGetSize();
char* DisplayGetScreen();

#endif