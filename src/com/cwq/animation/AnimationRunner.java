package com.cwq.animation;

import com.cwq.object.BaseObject;

public class AnimationRunner {
	
	private BaseObject object;
	private BaseAnimation animation;
	
	private float totalSElapsed = 0;
	private boolean isRun = true;
	
	public AnimationRunner(BaseObject object, BaseAnimation animation) {
		this.object = object;
		this.animation = animation;
	}
	
	public void runAnimation(double sElapsed) {
		if (isRun) {
			totalSElapsed += sElapsed;
			if (totalSElapsed > animation.getsDuration()) {
				isRun = false;
				totalSElapsed = animation.getsDuration();
				if (animation.isRevert()) {
					//还原到动画前
					animation.revert(object);
					return;
				}
			}
			animation.doAnimation(object, totalSElapsed);
		}
	}
	
	public void start() {
		isRun = true;
	}
	
	public void stop() {
		isRun = false;
	}
	
	public boolean isRun() {
		return isRun;
	}

}
