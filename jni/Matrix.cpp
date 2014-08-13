#include "Matrix.h"

void Matrix::orthoM(float* m, int mOffset, float left, float right,
					float bottom, float top, float near, float far) {
	if (left == right) {
/*		throw new IllegalArgumentException("left == right");*/
	}
	if (bottom == top) {
/*		throw new IllegalArgumentException("bottom == top");*/
	}
	if (near == far) {
/*		throw new IllegalArgumentException("near == far");*/
	}

	float r_width  = 1.0f / (right - left);
	float r_height = 1.0f / (top - bottom);
	float r_depth  = 1.0f / (far - near);
	float x =  2.0f * (r_width);
	float y =  2.0f * (r_height);
	float z = -2.0f * (r_depth);
	float tx = -(right + left) * r_width;
	float ty = -(top + bottom) * r_height;
	float tz = -(far + near) * r_depth;
	m[mOffset + 0] = x;
	m[mOffset + 5] = y;
	m[mOffset +10] = z;
	m[mOffset +12] = tx;
	m[mOffset +13] = ty;
	m[mOffset +14] = tz;
	m[mOffset +15] = 1.0f;
	m[mOffset + 1] = 0.0f;
	m[mOffset + 2] = 0.0f;
	m[mOffset + 3] = 0.0f;
	m[mOffset + 4] = 0.0f;
	m[mOffset + 6] = 0.0f;
	m[mOffset + 7] = 0.0f;
	m[mOffset + 8] = 0.0f;
	m[mOffset + 9] = 0.0f;
	m[mOffset + 11] = 0.0f;
}

void Matrix::translateM(float* m, int mOffset, float x, float y, float z) {
	for (int i=0 ; i<4 ; i++) {
		int mi = mOffset + i;
		m[12 + mi] += m[mi] * x + m[4 + mi] * y + m[8 + mi] * z;
	}
}

float Matrix::length(float x, float y, float z) {
	return (float) sqrt(x * x + y * y + z * z);
}

void Matrix::setLookAtM(float* rm, int rmOffset, float eyeX, float eyeY, float eyeZ,
						float centerX, float centerY, float centerZ,
						float upX, float upY, float upZ) {
	// See the OpenGL GLUT documentation for gluLookAt for a description
    // of the algorithm. We implement it in a straightforward way:

    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;

    // Normalize f
    float rlf = 1.0f / Matrix::length(fx, fy, fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;

    // compute s = f x up (x means "cross product")
    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;

    // and normalize s
    float rls = 1.0f / Matrix::length(sx, sy, sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;

    // compute u = s x f
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    rm[rmOffset + 0] = sx;
    rm[rmOffset + 1] = ux;
    rm[rmOffset + 2] = -fx;
    rm[rmOffset + 3] = 0.0f;

    rm[rmOffset + 4] = sy;
    rm[rmOffset + 5] = uy;
    rm[rmOffset + 6] = -fy;
    rm[rmOffset + 7] = 0.0f;

    rm[rmOffset + 8] = sz;
    rm[rmOffset + 9] = uz;
    rm[rmOffset + 10] = -fz;
    rm[rmOffset + 11] = 0.0f;

    rm[rmOffset + 12] = 0.0f;
    rm[rmOffset + 13] = 0.0f;
    rm[rmOffset + 14] = 0.0f;
    rm[rmOffset + 15] = 1.0f;

    translateM(rm, rmOffset, -eyeX, -eyeY, -eyeZ);
}

void Matrix::frustumM(float* m, int offset, float left, float right,
					  float bottom, float top, float near, float far) {
	if (left == right) {
/*		throw new IllegalArgumentException("left == right");*/
	}
	if (top == bottom) {
/*		throw new IllegalArgumentException("top == bottom");*/
	}
	if (near == far) {
/*		throw new IllegalArgumentException("near == far");*/
	}
	if (near <= 0.0f) {
/*		throw new IllegalArgumentException("near <= 0.0f");*/
	}
	if (far <= 0.0f) {
/*		throw new IllegalArgumentException("far <= 0.0f");*/
	}
	float r_width  = 1.0f / (right - left);
	float r_height = 1.0f / (top - bottom);
	float r_depth  = 1.0f / (near - far);
	float x = 2.0f * (near * r_width);
	float y = 2.0f * (near * r_height);
	float A = (right + left) * r_width;
	float B = (top + bottom) * r_height;
	float C = (far + near) * r_depth;
	float D = 2.0f * (far * near * r_depth);
	m[offset + 0] = x;
	m[offset + 5] = y;
	m[offset + 8] = A;
	m[offset +  9] = B;
	m[offset + 10] = C;
	m[offset + 14] = D;
	m[offset + 11] = -1.0f;
	m[offset +  1] = 0.0f;
	m[offset +  2] = 0.0f;
	m[offset +  3] = 0.0f;
	m[offset +  4] = 0.0f;
	m[offset +  6] = 0.0f;
	m[offset +  7] = 0.0f;
	m[offset + 12] = 0.0f;
	m[offset + 13] = 0.0f;
	m[offset + 15] = 0.0f;
}

void Matrix::multiplyMM(float* result, int resultOffset,
						float* lhs, int lhsOffset, float* rhs, int rhsOffset) {
	int i, j, k;
	for(i = 0; i < 4; i++) {
    	for(j =0; j < 4; j++) {
    		for(k = 0; k < 4; k++) {
    			result[resultOffset + i*4 + j] += lhs[lhsOffset + i*4 + k] * rhs[rhsOffset + k*4 + j];
    		}
    	}
    }
}