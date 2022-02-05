#include <awful/Mesh.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool str_contains(char *haystack, const char needle) {
  for (int i = 0; i < strlen(haystack); i++) {
    if (haystack[i] == needle) {
      return true;
    }
  }
  return false;
}

char **str_split(char *a_str, const char a_delim) {
  char **result = 0;
  size_t count = 0;
  char *tmp = a_str;
  char *last_comma = 0;
  char delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  /* Count how many elements will be extracted. */
  while (*tmp) {
    if (a_delim == *tmp) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }

  /* Add space for trailing token. */
  count += last_comma < (a_str + strlen(a_str) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc(sizeof(char *) * count);

  if (result) {
    size_t idx = 0;
    char *token = strtok(a_str, delim);

    while (token) {
      assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}

struct Mesh LoadOBJ(const char *path) {

  FILE *f;
  char buffer[128];
  f = fopen(path, "r");

  u16 vertexIdx = 0;

  struct Mesh m = GenMesh();

  while (fgets(buffer, 70, f) != NULL) {

    if (buffer[0] == 'v' && buffer[1] == ' ') {
      // Vertex

      char **parts = str_split(buffer, ' ');
      float x = strtof(parts[1], NULL);
      float y = strtof(parts[2], NULL);
      float z = strtof(parts[3], NULL);

      m.verts[vertexIdx] = CgmVec3_init(x, y, z);

      vertexIdx++;
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      // Index

      char **parts = str_split(buffer, ' ');
      int count = sizeof(parts) / sizeof(parts[0]);

      for (int i = 0; i < 3; i++) {
        char *group = parts[i + 1];
        if (str_contains(group, '/')) {
          // Split and take the first one
          char **splits = str_split(group, '/');
          m.indexes[m.count++] = atoi(splits[0]) - 1;
        } else {
          // Take it as-is
          m.indexes[m.count++] = atoi(group) - 1;
        }
      }
    }
  }
  fclose(f);

  return m;
}