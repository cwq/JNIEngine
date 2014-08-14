package com.cwq.object;

import android.opengl.GLES20;

public class Point extends GraphObject {
	
	public Point() {
		this(0, 0);
	}
	
	public Point(float x, float y) {
		setAttribute(x, y);
	}
	
	private void setAttribute(float x, float y) {
		if (attribute == null) {
			attribute = new float[3];
		}
		attribute[0] = 0;
		attribute[1] = 0;
		attribute[2] = 0;
		moveTo(x, y);
	}

	@Override
	public void draw(double sElapsed) {
		// TODO Auto-generated method stub
		super.draw(sElapsed, GLES20.GL_POINTS);
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		return false;
	}
	
}
