#ifndef H_MATRIX
#define H_MATRIX

struct Matrix{
    float data[9];
};

struct Matrix mat_new();
struct Matrix mat_clone(struct Matrix a);

struct Matrix mat_add(struct Matrix a,struct Matrix b);
struct Matrix mat_sub(struct Matrix a,struct Matrix b);

struct Matrix mat_mult(struct Matrix a,struct Matrix b);
struct Matrix mat_div(struct Matrix a,struct Matrix b);

#endif