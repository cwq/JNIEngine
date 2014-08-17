#include "FadeAnimation.h"

FadeAnimation::FadeAnimation(float duration) : BaseAnimation(duration) {
	fadeDeta = 0;
	startFade = 0;
}

void FadeAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		object->setAlphaTo(startFade + fadeDeta * sElapsed / sDuration);
	}
}

void FadeAnimation::revert(BaseObject* object) {
	object->setAlphaTo(startFade);
}

BaseAnimation* FadeAnimation::fade(float duration, float start, float end) {
	FadeAnimation* animation = new FadeAnimation(duration);
	animation->setStartFade(start);
	animation->setFade(end - start);
	return animation;
}