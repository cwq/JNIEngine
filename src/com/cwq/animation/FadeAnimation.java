package com.cwq.animation;

import com.cwq.object.BaseObject;

public class FadeAnimation extends BaseAnimation {
	
	private float fade = 0;
	private float startFade = 0;

	public FadeAnimation(float duration) {
		super(duration);
	}

	@Override
	void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			object.setAlphaTo(startFade + fade * sElapsed / sDuration);
		}
	}

	@Override
	void revert(BaseObject object) {
		// TODO Auto-generated method stub
		object.setAlphaTo(startFade);
	}

	public void setFade(float fade) {
		this.fade = fade;
	}

	public float getStartFade() {
		return startFade;
	}

	public void setStartFade(float startFade) {
		this.startFade = startFade;
	}
	
	public static BaseAnimation fade(float duration, float start, float end) {
		FadeAnimation animation = new FadeAnimation(duration);
		animation.setStartFade(start);
		float deta = end - start;
		animation.setFade(deta);
		return animation;
	}

}
