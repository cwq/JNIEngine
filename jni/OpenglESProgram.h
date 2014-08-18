#ifndef OPENGLESPROGRAM_H
#define OPENGLESPROGRAM_H

#include "OpenglESHelper.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class OpenglESProgram
{
protected:
	OpenglESProgram();
	
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

	glm::mat4 mProjMatrix; //投影
	glm::mat4 mVMatrix; //视图矩阵
	glm::mat4 mMVPMatrix; //复合矩阵

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
	float halfW;
	float halfH;

public:
	virtual ~OpenglESProgram();
	virtual void onSurfaceCreated();
	virtual void onSurfaceChanged(int width, int height);
	virtual void onDrawFrame();
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
	inline glm::mat4 getmProjMatrix() {
		return mProjMatrix;
	}
	inline glm::mat4 getmVMatrix() {
		return mVMatrix;
	}
	inline glm::mat4 getmMVPMatrix() {
		return mMVPMatrix;
	}
	inline float getHalfW() {
		return halfW;
	}
	inline float getHalfH() {
		return halfH;
	}
};

#endif // !OPENGLESPROGRAM_H
