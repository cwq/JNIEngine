#include "TintAnimation.h"

TintAnimation::TintAnimation(float duration) : BaseAnimation(duration) {
	r = g = b = alpha  = 0;
}

void TintAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		object->setColor(startColor[0] + r * sElapsed / sDuration,
			startColor[1] + g * sElapsed / sDuration,
			startColor[2] + b * sElapsed / sDuration, 
			startColor[3] + alpha * sElapsed / sDuration);
	}
}

void TintAnimation::revert(BaseObject* object) {
	object->setColor(startColor[0], startColor[1], startColor[2], startColor[3]);
}

BaseAnimation* TintAnimation::tint(float duration, float* startColor, float r, float g, float b, float alpha) {
	TintAnimation* animation = new TintAnimation(duration);
	animation->setStartColor(startColor);
	animation->setR(r);
	animation->setG(g);
	animation->setB(b);
	animation->setAlpha(alpha);
	return animation;
}