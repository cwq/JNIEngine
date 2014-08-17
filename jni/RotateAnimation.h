#ifndef ROTATEANIMATION_H
#define ROTATEANIMATION_H

#include "BaseAnimation.h"

class RotateAnimation : public BaseAnimation
{
private:
	float X;
	float Y;
	float Z;
	float angle;
	glm::mat4 startMatrix;

public:
	RotateAnimation(float duration);
	inline float getX() {
		return X;
	}
	inline void setX(float x) {
		X = x;
	}
	inline float getY() {
		return Y;
	}
	inline void setY(float y) {
		Y = y;
	}
	inline float getZ() {
		return Z;
	}
	inline void setZ(float z) {
		Z = z;
	}
	inline float getAngle() {
		return angle;
	}
	inline void setAngle(float angle) {
		this->angle = angle;
	}
	inline glm::mat4 getStartMatrix() {
		return startMatrix;
	}
	inline void setStartMatrix(glm::mat4 startMatrix) {
		this->startMatrix = startMatrix;
	}

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);

	static BaseAnimation* rotate(float duration, glm::mat4 startMatrix,
		float angle, float x, float y, float z);

};

#endif // !ROTATEANIMATION_H
