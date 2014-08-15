#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "OpenglESProgram.h"
#include "TextureManager.h"

class BaseObject
{
protected:
	BaseObject();
	virtual ~BaseObject();


	float* attribute;
	int pointNum;
	
	static const int FLOAT_BYTE;
	static const int POINT_DIMENSION;
	static const int UV_DIMENSION;

	float centerX;
	float centerY;
	float color[4];
	float alpha;
	/**
	 * alpha作用区域centerx, centery, halfW, halfH, 相对于图形中心,未乘变化矩阵前
	 */
	float inVec4[4];
	
	/**
	 * 图形显示区域centerx, centery, halfW, halfH, 乘变化矩阵后,屏幕坐标
	 */
	float showVec4[4];

	int zOrder;

/*	AnimationRunner animationRunner;*/

	glm::mat4 transMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;

	void doAnimation(double sElapsed);

public:
	inline int getzOrder() {
		return zOrder;
	}
	inline void setzOrder(int zOrder) {
		this->zOrder = zOrder;
	}
	inline float* getColor() {
		return color;
	}
	inline float getCenterX() {
		return centerX;
	}
	inline float getCenterY() {
		return centerY;
	}

	inline float getAlpha() {
		return alpha;
	}
	inline glm::mat4 getRotateMatrix() {
		return rotateMatrix;
	}

	inline void setAlphaBy(float deta) {
		this->alpha += deta;
	}
	inline void setAlphaTo(float alpha) {
		this->alpha = alpha;
	}

	float getScaleX();
	float getScaleY();

	void setShowVec4(float centerX, float centerY, float halfW, float halfH);
	void setInVec4(float centerX, float centerY, float halfW, float halfH);
	void setColor(float r, float g, float b, float a);

	void moveTo(float x, float y);
	void moveBy(float dx, float dy);
	void rotateBy(float angle, float x, float y, float z);
	void rotateTo(glm::mat4 rotate);
	void scaleTo(float scaleX, float scaleY);
	void scaleBy(float scaleX, float scaleY);

	bool isRunAnimation();
	void setAnimation(/*BaseAnimation animation*/);

	virtual void draw(OpenglESProgram* openglESProgram, double sElapsed) = 0;
	virtual bool isInObject(float x, float y) = 0;
	virtual void addTextureToManager();
};

#endif // !BASEOBJECT_H
