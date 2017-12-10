#ifndef _MATH_UTILS_HPP_
#define _MATH_UTILS_HPP_
#include <math.h>

float normalize_vector(float* _n);
void vector_product(const float _n[3],const float _t[3], float* _b);
float scalar_product(float _x[3], float _y[3]);
void reinit_vector_triplet(float* n,float* t, float* b,float* x, float* c_0,float& radius);

void rotate_x (float angle, float* vect);
void rotate_y (float angle, float* vect);
void rotate_z (float angle, float*vect);


#endif 
