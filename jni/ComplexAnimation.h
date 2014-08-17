#ifndef COMPLEXANIMATION_H
#define COMPLEXANIMATION_H

#include <list>

#include "BaseAnimation.h"

class ComplexAnimation : public BaseAnimation
{
private:
	std::list<BaseAnimation*> animations;
public:
	ComplexAnimation(float duration);
	void addAnimation(BaseAnimation* animation);
	void clear();

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);
};

#endif // !COMPLEXANIMATION_H
