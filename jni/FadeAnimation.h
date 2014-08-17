#ifndef FADEANIMATION_H
#define FADEANIMATION_H

#include "BaseAnimation.h"

class FadeAnimation : public BaseAnimation
{
private:
	float fadeDeta;
	float startFade;

public:
	FadeAnimation(float duration);
	inline void setFade(float fade) {
		fadeDeta = fade;
	}
	inline float getStartFade() {
		return startFade;
	}
	inline void setStartFade(float start) {
		startFade = start;
	}

	void doAnimation(BaseObject* object, float sElapsed);
	void revert(BaseObject* object);

	static BaseAnimation* fade(float duration, float start, float end);
};

#endif // !FADEANIMATION_H
