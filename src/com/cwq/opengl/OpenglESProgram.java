package com.cwq.opengl;

import android.opengl.GLES20;
import android.opengl.Matrix;

public abstract class OpenglESProgram {
	
	protected int program;
	protected int vertexLocation;
	protected int matrixLocation;
	protected int textureCoordinatesLocation;
	protected int textureUnitLocation;
	protected int colorLocation;
	protected int alphaLocation;
	protected int inVec4Location;
	protected int showVec4Location;
	protected int changeMatrixLocation;
	
	protected static final String vertexString = "a_position";
	protected static final String matrixString = "u_Matrix";
	protected static final String textureCoordinatesString = "a_TextureCoordinates";
	protected static final String textureUnitString = "u_TextureUnit";
	protected static final String colorString = "u_color";
	protected static final String alphaString = "u_alpha";
	protected static final String inVec4String = "u_inVec4";
	protected static final String showVec4String = "u_showVec4";
	protected static final String changeMatrixString = "u_changeMatrix";
	
	protected float[] mProjMatrix = new float[16]; //投影矩阵
	protected float[] mVMatrix = new float[16]; //视图矩阵
	protected float[] mMVPMatrix = new float[16]; //复合变化矩阵
	
	protected void init() {
		Matrix.setLookAtM(mVMatrix, 0, 0, 0, 0.1f, 0, 0, 0f, 0f, 1f, 0f);
	}
	
	public void release() {
		GLES20.glDeleteProgram(program);
	}
	
	public void onSurfaceChanged(float halfW, float halfH) {
		//正交投影
		Matrix.orthoM(mProjMatrix, 0, -halfW, halfW, -halfH, halfH, -1f, 1f);
		// 透视投影
//		Matrix.frustumM(mProjMatrix, 0, -halfW, halfW, -halfH, halfH, 0.1f, 100f);
		Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	}
	
	public int getProgram() {
		return program;
	}
	
	public int getVertexLocation() {
		return vertexLocation;
	}

	public int getMatrixLocation() {
		return matrixLocation;
	}

	public int getTextureCoordinatesLocation() {
		return textureCoordinatesLocation;
	}

	public int getTextureUnitLocation() {
		return textureUnitLocation;
	}

	public int getColorLocation() {
		return colorLocation;
	}

	public int getAlphaLocation() {
		return alphaLocation;
	}
	
	public int getInVec4Location() {
		return inVec4Location;
	}

	public int getShowVec4Location() {
		return showVec4Location;
	}

	public int getChangeMatrixLocation() {
		return changeMatrixLocation;
	}

	public float[] getmProjMatrix() {
		return mProjMatrix;
	}

	public float[] getmVMatrix() {
		return mVMatrix;
	}

	public float[] getmMVPMatrix() {
		return mMVPMatrix;
	}

}
