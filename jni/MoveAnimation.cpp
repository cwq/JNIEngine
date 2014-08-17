#include "MoveAnimation.h"

MoveAnimation::MoveAnimation(float duration) : BaseAnimation(duration) {

}

Point MoveAnimation::getStartPoint() {
	return startPoint;
}

Point MoveAnimation::getEndPoint() {
	return endPoint;
}

void MoveAnimation::setStartPoint(Point s) {
	startPoint = s;
}

void MoveAnimation::setEndPoint(Point e) {
	endPoint = e;
}

void MoveAnimation::doAnimation(BaseObject* object, float sElapsed) {
	if (sElapsed <= sDuration) {
		object->moveTo(startPoint.getX() + (endPoint.getX() - startPoint.getX()) * sElapsed / sDuration,
			startPoint.getY() + (endPoint.getY() - startPoint.getY()) * sElapsed / sDuration);
	}
}

void MoveAnimation::revert(BaseObject* object) {
	object->moveTo(startPoint.getX(), startPoint.getY());
}

BaseAnimation* MoveAnimation::move(float duration, Point start, Point end) {
	MoveAnimation* animation = new MoveAnimation(duration);
	animation->setStartPoint(start);
	animation->setEndPoint(end);
	return animation;
}
