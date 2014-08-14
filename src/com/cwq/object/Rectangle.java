package com.cwq.object;

public class Rectangle extends Polygon {
	
	private float halfW;
	private float halfH;
	
	public Rectangle(float w, float h) {
		this(0, 0, w, h, false);
	}
	
	public Rectangle(float w, float h, boolean isEmpty) {
		this(0, 0, w, h, isEmpty);
	}
	
	public Rectangle(float centerX, float centerY, float w, float h) {
		this(centerX, centerY, w, h, false);
	}
	
	public Rectangle(float centerX, float centerY, float w, float h, boolean isEmpty) {
		this.isEmpty = isEmpty;
		this.centerX = centerX;
		this.centerY = centerY;
		halfW = w / 2;
		halfH = h / 2;
		setAttribute();
	}
	
	private void setAttribute() {
		float[] attrib = {
				-halfW, halfH, 0.0f,
				-halfW, -halfH, 0.0f,
				halfW, -halfH, 0.0f,
				halfW, -halfH, 0.0f,
				halfW, halfH, 0.0f,
				-halfW, halfH, 0.0f,
		};
		attribute = attrib;
		moveTo(centerX, centerY);
	}

	public float getHalfW() {
		return halfW;
	}

	public float getHalfH() {
		return halfH;
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		return false;
	}

}
