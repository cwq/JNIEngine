package com.cwq.object;

import android.graphics.PointF;

public class Triangle extends Polygon {
	
	private PointF end1;
	private PointF end2;
	private PointF end3;
	
	public Triangle(PointF end1, PointF end2, PointF end3) {
		this(end1, end2, end3, false);
	}
	
	public Triangle(PointF end1, PointF end2, PointF end3, boolean isEmpty) {
		this.isEmpty = isEmpty;
		this.end1 = end1;
		this.end2 = end2;
		this.end3 = end3;
		setAttribute();
	}
	
	private void setAttribute() {
		if (attribute == null) {
			attribute = new float[9];
		}
		float centerX = (end1.x + end2.x + end3.x) / 3;
		float centerY = (end1.y + end2.y + end3.y) / 3;
		attribute[0] = end1.x - centerX;
		attribute[1] = end1.y - centerY;
		attribute[2] = 0;
		attribute[3] = end2.x - centerX;
		attribute[4] = end2.y - centerY;
		attribute[5] = 0;
		attribute[6] = end3.x - centerX;
		attribute[7] = end3.y - centerY;
		attribute[8] = 0;
		moveTo(centerX, centerY);
		setGLBuffer();
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		return false;
	}

}
