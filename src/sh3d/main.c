#include "viewer.h"
#include <awful/Awful.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("You need to specify a model... Dummy...\n");
    return 0;
  }

  u8 filelen = strlen(argv[1]);
  char *obj = ".OBJ";
  char ext[] = {argv[1][filelen - 4], argv[1][filelen - 3],
                argv[1][filelen - 2], argv[1][filelen - 1], 0};

  u8 i = 0;
  while (ext[i]) {
    ext[i] = toupper(ext[i]);
    if (ext[i] != obj[i]) {
      printf(
          "Daniel is lazy, and has only written the loader for .obj files... "
          "Try with one of those\n");
      return 0;
    }
    i++;
  }

  Run(argv[1]);

  return 0;
}
