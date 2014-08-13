package com.cwq.object;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import android.opengl.Matrix;
import com.cwq.animation.AnimationRunner;
import com.cwq.animation.BaseAnimation;
import com.cwq.opengl.OpenglESProgram;

public abstract class BaseObject {
	
	protected FloatBuffer glBuffer;
	protected float[] attribute;
	
	protected static final int FLOAT_BYTE = 4;
	protected static final int POINT_DIMENSION = 3;
	protected static final int UV_DIMENSION = 2;
	
	protected float centerX;
	protected float centerY;
	protected float[] color = {0.0f, 0.0f, 0.0f, 0.0f};
	protected float alpha = 1;
	/**
	 * alpha��������centerx, centery, halfW, halfH, �����ͼ������,δ�˱仯����ǰ
	 */
	protected float[] inVec4 = {0, 0, 1, 1};
	
	/**
	 * ͼ����ʾ����centerx, centery, halfW, halfH, �˱仯�����,��Ļ����
	 */
	protected float[] showVec4 = {0, 0, 10, 10};
	
	protected int zOrder = 0;
	
	public int getzOrder() {
		return zOrder;
	}

	public void setzOrder(int zOrder) {
		this.zOrder = zOrder;
	}
	
	public void setShowVec4(float centerX, float centerY, float halfW, float halfH) {
		showVec4[0] = centerX;
		showVec4[1] = centerY;
		showVec4[2] = halfW;
		showVec4[3] = halfH;
	}

	/**
	 * ͼ��������Ϊ����ԭ��
	 */
	public void setInVec4(float centerX, float centerY, float halfW, float halfH) {
		inVec4[0] = centerX;
		inVec4[1] = centerY;
		inVec4[2] = halfW;
		inVec4[3] = halfH;
	}
	
	protected AnimationRunner animationRunner;
	
	public float[] getColor() {
		return color;
	}

	public void setColor(float r, float g, float b, float a) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
		color[3] = a;
	}
	
	public float getAlpha() {
		return alpha;
	}
	
	public void setAlphaBy(float deta) {
		this.alpha += deta;
	}

	public void setAlphaTo(float alpha) {
		this.alpha = alpha;
	}

	protected float[] mtransMatrix = {
			1f, 0f, 0f, 0f,
			0f, 1f, 0f, 0f,
			0f, 0f, 1f, 0f,
			0f, 0f, 0f, 1f
	};
	
	protected float[] mrotateMatrix = {
			1f, 0f, 0f, 0f,
			0f, 1f, 0f, 0f,
			0f, 0f, 1f, 0f,
			0f, 0f, 0f, 1f
	};
	
	protected float[] mscaleMatrix = {
			1f, 0f, 0f, 0f,
			0f, 1f, 0f, 0f,
			0f, 0f, 1f, 0f,
			0f, 0f, 0f, 1f
	};
	
	public float[] getRotateMatrix() {
		return mrotateMatrix;
	}
	
	public float getCenterX() {
		return centerX;
	}
	
	public float getCenterY() {
		return centerY;
	}
	
	public void moveTo(float x, float y) {
		centerX = x;
		centerY = y;
		mtransMatrix[12] = x;
		mtransMatrix[13] = y;
	}
	
	public void moveBy(float dx, float dy) {
		centerX += dx;
		centerY += dy;
		mtransMatrix[12] += dx;
		mtransMatrix[13] += dy;
	}
	
	public void rotateBy(float angle, float x, float y, float z) {
		Matrix.rotateM(mrotateMatrix, 0, angle, x, y, z);
	}
	
	public void rotateTo(float[] rotateMatrix) {
		mrotateMatrix = rotateMatrix;
	}
	
	public float getScaleX() {
		return mscaleMatrix[0];
	}
	
	public float getScaleY() {
		return mscaleMatrix[5];
	}
	
	public void scaleTo(float scaleX, float scaleY) {
		mscaleMatrix[0] = scaleX;
		mscaleMatrix[5] = scaleY;
	}
	
	public void scaleBy(float scaleX, float scaleY) {
		Matrix.scaleM(mscaleMatrix, 0, scaleX, scaleY, 1);
	}
	
	protected void setGLBuffer() {
		if (glBuffer == null) {
			glBuffer = ByteBuffer.allocateDirect(attribute.length * FLOAT_BYTE)
					.order(ByteOrder.nativeOrder()).asFloatBuffer();
		} else {
			glBuffer.clear();
		}
		glBuffer.put(attribute);
	}
	
	public boolean isRunAnimation() {
		return animationRunner != null && animationRunner.isRun();
	}
	
	public void setAnimation(BaseAnimation animation) {
//		if (animationRunner == null || !animationRunner.isRun()) {
			animationRunner = new AnimationRunner(this, animation);
//		}
	}
	
	protected void doAnimation(double sElapsed) {
		if (animationRunner != null) {
			animationRunner.runAnimation(sElapsed);
		}
	}
	
	public abstract void draw(OpenglESProgram openglESProgram, double sElapsed);
	
	public abstract boolean isInObject(float x, float y);
	
	public void addTextureToManager() {
		
	}

}
