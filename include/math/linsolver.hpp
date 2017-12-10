/*
 * linsolver.h
 *
 *  Created on: 14 Jun 2014
 *      Author: kenny
 */
#ifndef _LINSOLVER_HPP_
#define _LINSOLVER_HPP_

#define ABS(X) X < 0 ? -X:X
#define MIN(X,Y) X<Y ? X:Y
#define MAX(X,Y) MIN(-X,-Y)



//implement gaussian elimination with pivoting!
int gaussianElimination (float* a,float* p_b,float* x,const int n );

//solves the equation Ax=b, using the LU decomposition method;
int _nxn_LUdecomposition(float* A,float*b, float* L, float* U ,const int n,float* x);
//performs the LU decomposition of a matrix A (if possible) 
int LUdecompose(float* A,float* L, float* U,const int n);

//utility functions
//the forward and backward substitutions, respectively.
int forwardSubstitute(float* a, float* b, float* y,const int n);

int backwardSubstitute(float* a,float* b,float* x, const int n);

//print the matrix in a nice form. n is the number of columns, and m the number of rows
int printmatrix(float* a,const int n, const int m);

//returns the absolute value of x
float absolute(float x);

//swaps row i and row "index_largest" of the extended matrix a|b
int swap(float* a,float* p_b,int index_largest,int i,const int n );

int multiply_add(float* a,float * p_b, const int n,int i,int j);



#endif /* LINSOLVER_H_ */

