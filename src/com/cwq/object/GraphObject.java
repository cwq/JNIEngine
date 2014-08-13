package com.cwq.object;

import android.opengl.GLES20;
import android.opengl.Matrix;

import com.cwq.opengl.OpenglESProgram;

public abstract class GraphObject extends BaseObject {

	protected static final int STRIDE = (POINT_DIMENSION) * FLOAT_BYTE;
	
	public float lineWidth = 5;
	
	public void setLineWidth(float width) {
		lineWidth = width;
	}
	
	protected GraphObject() {
		setColor(0, 0, 0, 1);
		setInVec4(0, 0, 0, 0);
	}
	
	protected void draw(OpenglESProgram openglESProgram, double sElapsed, int mode) {
		doAnimation(sElapsed);
		
		GLES20.glUseProgram(openglESProgram.getProgram());
		
		GLES20.glLineWidth(lineWidth);
		
		glBuffer.position(0);
		GLES20.glVertexAttribPointer(openglESProgram.getVertexLocation(), POINT_DIMENSION, GLES20.GL_FLOAT, false, STRIDE, glBuffer);
		
		glBuffer.position(POINT_DIMENSION);
		GLES20.glVertexAttribPointer(openglESProgram.getTextureCoordinatesLocation(), UV_DIMENSION, GLES20.GL_FLOAT, false, STRIDE, glBuffer);
		
		GLES20.glEnableVertexAttribArray(openglESProgram.getVertexLocation());
		GLES20.glEnableVertexAttribArray(openglESProgram.getTextureCoordinatesLocation());
		
		GLES20.glUniform4fv(openglESProgram.getColorLocation(), 1, color, 0);
		GLES20.glUniform1f(openglESProgram.getAlphaLocation(), alpha);
		
		GLES20.glUniform4fv(openglESProgram.getInVec4Location(), 1, inVec4, 0);
		
		GLES20.glUniform4fv(openglESProgram.getShowVec4Location(), 1, showVec4, 0);
		
		float[] tempMatrix = new float[16];
		float[] complexMatrix = new float[16];
		float[] finalMatrix = new float[16];
		Matrix.multiplyMM(tempMatrix, 0, mrotateMatrix, 0, mscaleMatrix, 0);
		Matrix.multiplyMM(complexMatrix, 0, mtransMatrix, 0, tempMatrix, 0);
		
		GLES20.glUniformMatrix4fv(openglESProgram.getChangeMatrixLocation(), 1, false, complexMatrix, 0);
		
		Matrix.multiplyMM(finalMatrix, 0, openglESProgram.getmMVPMatrix(), 0, complexMatrix, 0);
		// 应用投影和视口变换
		GLES20.glUniformMatrix4fv(openglESProgram.getMatrixLocation(), 1, false, finalMatrix, 0);
		
		//Set the active texture unit to texture unit 0.
		GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
		// Bind the texture to this unit
		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
		//read from texture unit 0.
		GLES20.glUniform1f(openglESProgram.getTextureUnitLocation(), 0);
		
		GLES20.glDrawArrays(mode, 0, attribute.length / (POINT_DIMENSION));
		
		GLES20.glDisableVertexAttribArray(openglESProgram.getVertexLocation());
		GLES20.glDisableVertexAttribArray(openglESProgram.getTextureCoordinatesLocation());
	}
}
