package com.cwq.animation;

import java.util.ArrayList;
import java.util.List;

import com.cwq.object.BaseObject;

public class ComplexAnimation extends BaseAnimation {
	
	private List<BaseAnimation> animations;

	public ComplexAnimation(float duration) {
		super(duration);
		// TODO Auto-generated constructor stub
		animations = new ArrayList<BaseAnimation>();
	}

	@Override
	void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			for (BaseAnimation animation : animations) {
				animation.doAnimation(object, sElapsed);
			}
		}
	}

	@Override
	void revert(BaseObject object) {
		// TODO Auto-generated method stub
		for (BaseAnimation animation : animations) {
			animation.revert(object);
		}
	}
	
	public void addAnimation(BaseAnimation animation) {
		animations.add(animation);
		if (animation.sDuration > this.sDuration) {
			this.sDuration = animation.sDuration;
		}
	}
	
	public void clear() {
		animations.clear();
		sDuration = 0;
	}

}
