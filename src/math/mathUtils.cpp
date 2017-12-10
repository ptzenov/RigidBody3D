#include <math/mathUtils.hpp>

float normalize_vector(float* _n) {

	float norm = 0;
	for (int d = 0; d < 3; d++)
		norm += _n[d] * _n[d];
	norm = sqrt(norm);
	// unless we are dealing with an empty vector...
	if (norm != 0)
		for (int d = 0; d < 3; d++)
			_n[d] /= norm;

	return norm;

}

void vector_product(const float _n[3], const float _t[3], float* _b) {
	_b[0] = _n[1] * _t[2] - _n[2] * _t[1];
	_b[1] = _n[2] * _t[0] - _n[0] * _t[2];
	_b[2] = _n[0] * _t[1] - _n[1] * _t[0];
}

float scalar_product(float _x[3], float _y[3]) {
	float sum = 0;

	for (int d = 0; d < 3; d++)
		sum += _x[d] * _y[d];

	return sum;
}


void rotate_x(float angle, float* vect) {

	float c = cos(angle);
	float s = sin(angle);
	float tmp1 = c * vect[1] - s * vect[2];
	float tmp2 = s * vect[1] + c * vect[2];
	vect[1] = tmp1;
	vect[2] = tmp2;
}

void rotate_y(float angle, float* vect) {
	float c = cos(angle);
	float s = sin(angle);
	float tmp0 = c * vect[0] + s * vect[2];
	float tmp2 = -s * vect[0] + c * vect[2];
	vect[0] = tmp0;
	vect[2] = tmp2;

}

void rotate_z(float angle, float*vect) {

	float c = cos(angle);
	float s = sin(angle);
	float tmp0 = c * vect[0] - s * vect[1];
	float tmp1 = s * vect[0] - c * vect[1];
	vect[0] = tmp0;
	vect[1] = tmp1;

}


void reinit_vector_triplet(float* n,float* t, float* b,float* x, float* c_0,float& radius)
{
	normalize_vector(n);
	for (int d = 0; d < 3; d++)
		 t[d] = x[d] - c_0[d]; // t_vector does NOT lie on the plane determined by n_vect!!!!

	//take the radius!
	radius = normalize_vector(t);
	vector_product(n, t, b);
	normalize_vector(b); //not needed !!!b should already have norm 1!
}


