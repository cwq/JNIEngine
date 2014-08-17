#ifndef SCALEANIMATION_H
#define SCALEANIMATION_H

#include "BaseAnimation.h"

class ScaleAnimation : public BaseAnimation
{
private:
	float startScaleX;
	float startScaleY;
	float scaleX;
	float scaleY;

public:
	ScaleAnimation(float duration);
	inline float getStartScaleX() {
		return startScaleX;
	}
	inline float getStartScaleY() {
		return startScaleY;
	}
	inline void setStartScale(float startX, float startY) {
		startScaleX = startX;
		startScaleY = startY;
	}
	inline void setScale(float sx, float sy) {
		scaleX = sx;
		scaleY = sy;
	}

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);

	static BaseAnimation* scale(float duration, float startX, float endX, float startY, float endY);
};

#endif // !SCALEANIMATION_H
