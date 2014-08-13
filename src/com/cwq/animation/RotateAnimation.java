package com.cwq.animation;

import com.cwq.object.BaseObject;

import android.opengl.Matrix;

public class RotateAnimation extends BaseAnimation {
	
	private float X = 0;
	private float Y = 0;
	private float Z = 0;
	private float angle = 0;
	
	private float[] startMatrix;

	public RotateAnimation(float duration) {
		super(duration);
		// TODO Auto-generated constructor stub
	}

	@Override
	void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			float[] temp = startMatrix.clone();
			Matrix.rotateM(temp, 0, angle * sElapsed / sDuration, X, Y, Z);
			object.rotateTo(temp);
		}
	}

	@Override
	void revert(BaseObject object) {
		// TODO Auto-generated method stub
		object.rotateTo(startMatrix);
	}
	
	public float getX() {
		return X;
	}

	public void setX(float x) {
		X = x;
	}

	public float getY() {
		return Y;
	}

	public void setY(float y) {
		Y = y;
	}

	public float getZ() {
		return Z;
	}

	public void setZ(float z) {
		Z = z;
	}

	public float getAngle() {
		return angle;
	}

	public void setAngle(float angle) {
		this.angle = angle;
	}
	
	public float[] getStartMatrix() {
		return startMatrix;
	}

	public void setStartMatrix(float[] startMatrix) {
		this.startMatrix = startMatrix;
	}

	public static BaseAnimation rotate(float duration, float[] startMatrix, float angle, float x, float y, float z) {
		RotateAnimation animation = new RotateAnimation(duration);
		animation.setStartMatrix(startMatrix.clone());
		animation.setX(x);
		animation.setY(y);
		animation.setZ(z);
		animation.setAngle(angle);
		return animation;
	}

}
