#include "ComplexAnimation.h"

ComplexAnimation::ComplexAnimation(float duration) : BaseAnimation(duration) {
	animations = std::list<BaseAnimation*>();
}

void ComplexAnimation::addAnimation(BaseAnimation* animation) {
	animations.push_back(animation);
}

void ComplexAnimation::clear() {
	animations.clear();
	sDuration = 0;
}

void ComplexAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		for (std::list<BaseAnimation*>::iterator it = animations.begin(); it != animations.end(); ++it) {
			(*it)->doAnimation(object, sElapsed);
		}
	}
}

void ComplexAnimation::revert(BaseObject* object) {
	for (std::list<BaseAnimation*>::iterator it = animations.begin(); it != animations.end(); ++it) {
		(*it)->revert(object);
	}
}