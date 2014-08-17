#ifndef TINTANIMATION_H
#define TINTANIMATION_H

#include "BaseAnimation.h"

class TintAnimation : BaseAnimation
{
private:
	float r;
	float g;
	float b;
	float alpha;
	float startColor[4];

public:
	TintAnimation(float duration);
	inline float getR() {
		return r;
	}
	inline void setR(float r) {
		this->r = r;
	}
	inline float getG() {
		return g;
	}
	inline void setG(float g) {
		this->g = g;
	}
	inline float getB() {
		return b;
	}
	inline void setB(float b) {
		this->b = b;
	}
	inline float getAlpha() {
		return alpha;
	}
	inline void setAlpha(float alpha) {
		this->alpha = alpha;
	}
	inline float* getStartColor() {
		return startColor;
	}
	inline void setStartColor(float* startColor) {
		this->startColor[0] = startColor[0];
		this->startColor[1] = startColor[1];
		this->startColor[2] = startColor[2];
		this->startColor[3] = startColor[3];
	}

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);

	static BaseAnimation* tint(float duration, float* startColor,
		float r, float g, float b, float alpha);
};

#endif // !TINTANIMATION_H
