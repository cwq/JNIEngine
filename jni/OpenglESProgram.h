#ifndef OPENGLESPROGRAM_H
#define OPENGLESPROGRAM_H

#include "OpenglESHelper.h"

class OpenglESProgram
{
protected:
	OpenglESProgram();
	~OpenglESProgram();
	
	int program;
	int vertexLocation;
	int matrixLocation;
	int textureCoordinatesLocation;
	int textureUnitLocation;
	int colorLocation;
	int alphaLocation;
	int inVec4Location;
	int showVec4Location;
	int changeMatrixLocation;

	float mProjMatrix[16]; //投影矩阵
	float mVMatrix[16]; //视图矩阵
	float mMVPMatrix[16]; //复合变化矩阵

	static const char* vertexString;
	static const char* matrixString;
	static const char* textureCoordinatesString;
	static const char* textureUnitString;
	static const char* colorString;
	static const char* alphaString;
	static const char* inVec4String;
	static const char* showVec4String;
	static const char* changeMatrixString;

	static const int R_INDEX;
	static const int G_INDEX;
	static const int B_INDEX;
	static const int A_INDEX;

	float bgColor[4];

public:
	void onSurfaceCreated();
	void onSurfaceChanged(int width, int height);
	void onDrawFrame();
	void setBgColor(float r, float g, float b, float alpha);
	inline int getProgram() {
		return program;
	}
	inline int getVertexLocation() {
		return vertexLocation;
	}
	inline int getMatrixLocation() {
		return matrixLocation;
	}
	inline int getTextureCoordinatesLocation() {
		return textureCoordinatesLocation;
	}
	inline int getTextureUnitLocation() {
		return textureUnitLocation;
	}
	inline int getColorLocation() {
		return colorLocation;
	}
	inline int getAlphaLocation() {
		return alphaLocation;
	}
	inline int getInVec4Location() {
		return inVec4Location;
	}
	inline int getShowVec4Location() {
		return showVec4Location;
	}
	inline int getChangeMatrixLocation() {
		return changeMatrixLocation;
	}
	inline float* getmProjMatrix() {
		return mProjMatrix;
	}
	inline float* getmVMatrix() {
		return mVMatrix;
	}
	inline float* getmMVPMatrix() {
		return mMVPMatrix;
	}
};

#endif // !OPENGLESPROGRAM_H