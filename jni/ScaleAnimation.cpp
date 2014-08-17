#include "ScaleAnimation.h"

ScaleAnimation::ScaleAnimation(float duration) : BaseAnimation(duration) {
	startScaleX = startScaleY = scaleX = scaleY = 0;
}

void ScaleAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		object->scaleTo(startScaleX + scaleX * sElapsed / sDuration,
			startScaleY + scaleY * sElapsed / sDuration);
	}
}

void ScaleAnimation::revert(BaseObject* object) {
	object->scaleTo(startScaleX, startScaleY);
}

BaseAnimation* ScaleAnimation::scale(float duration, float startX, float endX, float startY, float endY) {
	ScaleAnimation* animation = new ScaleAnimation(duration);
	animation->setStartScale(startX, startY);
	animation->setScale(endX - startX, endY - startY);
	return animation;
}