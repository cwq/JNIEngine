package com.cwq.object;

import android.opengl.GLES20;

import com.cwq.opengl.OpenglESProgram;

public abstract class Polygon extends GraphObject {
	
	protected boolean isEmpty;
	
	public boolean isEmpty() {
		return isEmpty;
	}

	public void setEmpty(boolean isEmpty) {
		this.isEmpty = isEmpty;
	}

	@Override
	public void draw(OpenglESProgram openglESProgram, double sElapsed) {
		// TODO Auto-generated method stub
		if (isEmpty) {
			super.draw(openglESProgram, sElapsed, GLES20.GL_LINE_LOOP);
		} else {
			super.draw(openglESProgram, sElapsed, GLES20.GL_TRIANGLES);
		}
	}

}
