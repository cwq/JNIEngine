#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

class Matrix
{
public:
	/************************************************************************/
	/* Computes an orthographic projection matrix.                                                                     */
	/************************************************************************/
	static void orthoM(float* m, int mOffset, float left, float right, 
		float bottom, float top, float near, float far);

	/************************************************************************/
	/* Translates matrix m by x, y, and z in place.                                                                   */
	/************************************************************************/
	static void translateM(float* m, int mOffset, float x, float y, float z);

	/************************************************************************/
	/* Defines a viewing transformation in terms of an eye point, a center of
	/* view, and an up vector.
	/************************************************************************/
	static void setLookAtM(float* rm, int rmOffset,
		float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);

	/************************************************************************/
	/* Multiplies two 4x4 matrices together and stores the result in a third 4x4 matrix                                                                    */
	/************************************************************************/
	static void multiplyMM(float* result, int resultOffset,
		float* lhs, int lhsOffset, float* rhs, int rhsOffset);

	/************************************************************************/
	/* Computes the length of a vector                                                                     */
	/************************************************************************/
	static float length(float x, float y, float z);

	/************************************************************************/
	/* Defines a projection matrix in terms of six clip planes                                                                     */
	/************************************************************************/
	static void frustumM(float* m, int offset,
		float left, float right, float bottom, float top,
		float near, float far);
};

#endif // !MATRIX_H
