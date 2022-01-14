#ifndef H_MATRIX
#define H_MATRIX

#define MAT_LEN 4 * 4

struct Matrix {
  float data[MAT_LEN];
};

struct Matrix mat_new();
struct Matrix mat_clone(struct Matrix a);

struct Matrix mat_add(struct Matrix a, struct Matrix b);
struct Matrix mat_sub(struct Matrix a, struct Matrix b);

struct Matrix mat_mult(struct Matrix a, struct Matrix b);
struct Matrix mat_div(struct Matrix a, struct Matrix b);

struct Matrix createProjection(float fov, float aspect, float znear,
                               float zfar);

#endif