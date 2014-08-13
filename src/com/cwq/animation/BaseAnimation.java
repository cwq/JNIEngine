package com.cwq.animation;

import com.cwq.object.BaseObject;

public abstract class BaseAnimation {
	
	protected float sDuration = 0;
	protected boolean isRevert = false;
	
	public BaseAnimation(float duration) {
		sDuration = duration;
	}

	public float getsDuration() {
		return sDuration;
	}

	public void setsDuration(float sDuration) {
		this.sDuration = sDuration;
	}

	public boolean isRevert() {
		return isRevert;
	}

	public void setRevert(boolean isRevert) {
		this.isRevert = isRevert;
	}
	
	abstract void doAnimation(BaseObject object, float sElapsed);
	
	abstract void revert(BaseObject object);

}
