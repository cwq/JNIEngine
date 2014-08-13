package com.cwq.object;

import android.graphics.PointF;
import android.opengl.GLES20;

import com.cwq.opengl.OpenglESProgram;

public class Line extends GraphObject {
	
	private PointF start;
	private PointF end;
	
	public Line(PointF end) {
		this(new PointF(0, 0), end);
	}
	
	public Line(PointF start, PointF end) {
		this.start = start;
		this.end = end;
		setAttribute();
	}
	
	private void setAttribute() {
		if (attribute == null) {
			attribute = new float[6];
		}
		float centerX = (start.x + end.x) / 2;
		float centerY = (start.y + end.y) / 2;
		attribute[0] = start.x - centerX;
		attribute[1] = start.y - centerY;
		attribute[2] = 0;
		attribute[3] = end.x - centerX;
		attribute[4] = end.y - centerY;
		attribute[5] = 0;
		moveTo(centerX, centerY);
		setGLBuffer();
	}

//	public PointF getStart() {
//		return start;
//	}
//
//	public void setStart(PointF start) {
//		setStartEnd(start, end);
//	}
//
//	public PointF getEnd() {
//		return end;
//	}
//
//	public void setEnd(PointF end) {
//		setStartEnd(start, end);
//	}
//	
//	public void setStartEnd(PointF start, PointF end) {
//		this.start = start;
//		this.end = end;
//		setAttribute();
//	}

	@Override
	public void draw(OpenglESProgram openglESProgram, double sElapsed) {
		// TODO Auto-generated method stub
		super.draw(openglESProgram, sElapsed, GLES20.GL_LINES);
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		return false;
	}

}
