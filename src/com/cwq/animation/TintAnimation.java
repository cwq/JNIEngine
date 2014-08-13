package com.cwq.animation;

import com.cwq.object.BaseObject;

public class TintAnimation extends BaseAnimation {
	
	private float r = 0;
	private float g = 0;
	private float b = 0;
	private float alpha = 0;
	
	private float[] startColor;

	public TintAnimation(float duration) {
		super(duration);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			object.setColor(startColor[0] + r * sElapsed / sDuration,
					startColor[1] + g * sElapsed / sDuration,
					startColor[2] + b * sElapsed / sDuration, 
					startColor[3] + alpha * sElapsed / sDuration);
		}
	}

	@Override
	public void revert(BaseObject object) {
		// TODO Auto-generated method stub
		object.setColor(startColor[0], startColor[1], startColor[2], startColor[3]);
	}
	
	public float getR() {
		return r;
	}

	public void setR(float r) {
		this.r = r;
	}

	public float getG() {
		return g;
	}

	public void setG(float g) {
		this.g = g;
	}

	public float getB() {
		return b;
	}

	public void setB(float b) {
		this.b = b;
	}

	public float getAlpha() {
		return alpha;
	}

	public void setAlpha(float alpha) {
		this.alpha = alpha;
	}
	
	public float[] getStartColor() {
		return startColor;
	}

	public void setStartColor(float[] startColor) {
		this.startColor = startColor;
	}

	public static BaseAnimation tint(float duration, float[] startColor, float r, float g, float b, float alpha) {
		TintAnimation animation = new TintAnimation(duration);
		animation.setStartColor(startColor.clone());
		animation.setR(r);
		animation.setG(g);
		animation.setB(b);
		animation.setAlpha(alpha);
		return animation;
	}

}
