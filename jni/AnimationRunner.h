#ifndef ANIMATIONRUNNER_H
#define ANIMATIONRUNNER_H

#include "BaseAnimation.h"

class BaseObject;
class BaseAnimation;

class AnimationRunner
{
private:
	BaseObject* object;
	BaseAnimation* animation;

	float totalSElapsed;
	bool run;

public:
	AnimationRunner(BaseObject* object, BaseAnimation* animation);
	void runAnimation(double sElapsed);

	inline void start() {
		run = true;
	}
	inline void stop() {
		run = false;
	}
	inline bool isRun() {
		return run;
	}
};

#endif // !ANIMATIONRUNNER_H
