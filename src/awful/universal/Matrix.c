#include <awful/Matrix.h>

struct Matrix mat_new() {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = 0.0F;
  }

  return matrix;
}

struct Matrix mat_clone(struct Matrix a) {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = a.data[i];
  }

  return matrix;
}

struct Matrix mat_add(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = a.data[i] + a.data[i];
  }

  return matrix;
}

struct Matrix mat_sub(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = a.data[i] - a.data[i];
  }

  return matrix;
}

struct Matrix mat_mult(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = a.data[i] * a.data[i];
  }

  return matrix;
}

struct Matrix mat_div(struct Matrix a, struct Matrix b) {
  struct Matrix matrix;

  for (int i = 0; i < MAT_LEN; i++) {
    matrix.data[i] = a.data[i] / a.data[i];
  }

  return matrix;
}

struct Matrix createProjection(float fov, float aspect, float znear, float zfar) {

    float ymax, xmax;
    ymax = (float) (znear * tan(fov * (3.141592F) / 360.0));
    xmax = ymax * aspect;
    struct Matrix result = mat_new();
    glhFrustumf2(&result, -xmax, xmax, -ymax, ymax, znear, zfar);
    return result;
}

void glhFrustumf2(struct Matrix *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
    float twoZNear, deltaW, deltaH, deltaZ;
    twoZNear = 2.0f * znear;
    deltaW = right - left;
    deltaH = top - bottom;
    deltaZ= zfar - znear;
    matrix->data[0] = twoZNear / deltaW;
    matrix->data[1] = 0.0f;
    matrix->data[2] = 0.0f;
    matrix->data[3] = 0.0f;
    matrix->data[4] = 0.0f;
    matrix->data[5] = twoZNear / deltaH;
    matrix->data[6] = 0.0f;
    matrix->data[7] = 0.0f;
    matrix->data[8] = (right + left) / deltaW;
    matrix->data[9] = (top + bottom) / deltaH;
    matrix->data[10] = (-zfar - znear) / deltaZ;
    matrix->data[11] = -1.0f;
    matrix->data[12] = 0.0f;
    matrix->data[13] = 0.0f;
    matrix->data[14] = (-twoZNear * zfar) / deltaZ;
    matrix->data[15] = 0.0f;
}