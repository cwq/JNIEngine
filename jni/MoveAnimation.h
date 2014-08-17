#ifndef MOVEANIMATION_H
#define MOVEANIMATION_H

#include "BaseAnimation.h"
#include "Point.h"

class MoveAnimation : public BaseAnimation
{
private:
	Point startPoint;
	Point endPoint;

public:
	MoveAnimation(float duration);
	Point getStartPoint();
	Point getEndPoint();
	void setStartPoint(Point s);
	void setEndPoint(Point e);

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);

	static BaseAnimation* move(float duration, Point start, Point end);
};

#endif // !MOVEANIMATION_H
