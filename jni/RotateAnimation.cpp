#include "RotateAnimation.h"

RotateAnimation::RotateAnimation(float duration) : BaseAnimation(duration) {
	X = Y = Z = angle = 0;
}

void RotateAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		object->rotateTo(glm::rotate(startMatrix,
				angle * sElapsed / sDuration, glm::vec3(X, Y, Z)));
	}
}

void RotateAnimation::revert(BaseObject* object) {
	object->rotateTo(startMatrix);
}

BaseAnimation* RotateAnimation::rotate(float duration, glm::mat4 startMatrix,
									   float angle, float x, float y, float z) {
	RotateAnimation* animation = new RotateAnimation(duration);
	animation->setStartMatrix(startMatrix);
	animation->setX(x);
	animation->setY(y);
	animation->setZ(z);
	animation->setAngle(angle);
	return animation;
}
