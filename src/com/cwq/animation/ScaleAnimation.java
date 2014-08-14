package com.cwq.animation;

import com.cwq.object.BaseObject;

public class ScaleAnimation extends BaseAnimation {
	
	private float startScaleX;
	private float startScaleY;

	private float scaleX;
	private float scaleY;

	public ScaleAnimation(float duration) {
		super(duration);
		// TODO Auto-generated constructor stub
	}
	

	@Override
	public void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			object.scaleTo(startScaleX + scaleX * sElapsed / sDuration,
					startScaleY + scaleY * sElapsed / sDuration);
		}
	}

	@Override
	public void revert(BaseObject object) {
		// TODO Auto-generated method stub
		object.scaleTo(startScaleX, startScaleY);
	}

	public float getStartScaleX() {
		return startScaleX;
	}
	
	public float getStartScaleY() {
		return startScaleY;
	}

	public void setStartScale(float startX, float startY) {
		startScaleX = startX;
		startScaleY = startY;
	}

	public void setScale(float sx, float sy) {
		scaleX = sx;
		scaleY = sy;
	}
	
	public static BaseAnimation scaleTo(float duration, float startX, float endX, float startY, float endY) {
		ScaleAnimation animation = new ScaleAnimation(duration);
		animation.setStartScale(startX, startY);
		animation.setScale(endX - startX, endY - startY);
		return animation;
	}

}
