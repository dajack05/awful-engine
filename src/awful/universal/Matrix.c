#include <awful/Matrix.h>

struct Matrix mat_new() {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = 0.0F;
  }

  return matrix;
}

struct Matrix mat_clone(struct Matrix a) {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = a.data[i];
  }

  return matrix;
}

struct Matrix mat_add(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = a.data[i] + a.data[i];
  }

  return matrix;
}

struct Matrix mat_sub(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = a.data[i] - a.data[i];
  }

  return matrix;
}

struct Matrix mat_mult(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = a.data[i] * a.data[i];
  }

  return matrix;
}

struct Matrix mat_div(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < 9; i++) {
    matrix.data[i] = a.data[i] / a.data[i];
  }

  return matrix;
}
