package com.cwq.opengl;

import com.cwq.engine.CutActivity;

import android.opengl.GLES20;
import android.util.Log;

public class ComOGLESProgram extends OpenglESProgram{
	
	public ComOGLESProgram() {
		init();
	}
	
	@Override
	protected void init() {
		// TODO Auto-generated method stub
		super.init();
		try {
			int vertexShader = OpenglESHelper.loadShader(GLES20.GL_VERTEX_SHADER, vertexShaderString);
			int fragmentShader = OpenglESHelper.loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderString);
			program = GLES20.glCreateProgram();
			if (program == 0) {
				throw new Exception("error occurs creating the program");
			}
			
			GLES20.glAttachShader(program, vertexShader);
			GLES20.glAttachShader(program, fragmentShader);
			GLES20.glLinkProgram(program);
			int[] linkStatus = new int[1];
			GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkStatus, 0);
			if (linkStatus[0] == 0) {
				GLES20.glDeleteProgram(program);
				throw new Exception("Could not link program: " + GLES20.glGetProgramInfoLog(program));
			}
			
			vertexLocation = GLES20.glGetAttribLocation(program, vertexString);
			matrixLocation = GLES20.glGetUniformLocation(program, matrixString);
			colorLocation = GLES20.glGetUniformLocation(program, colorString);
			alphaLocation = GLES20.glGetUniformLocation(program, alphaString);
			textureCoordinatesLocation = GLES20.glGetAttribLocation(program, textureCoordinatesString);
			textureUnitLocation = GLES20.glGetUniformLocation(program, textureUnitString);
			inVec4Location = GLES20.glGetUniformLocation(program, inVec4String);
			showVec4Location = GLES20.glGetUniformLocation(program, showVec4String);
			changeMatrixLocation = GLES20.glGetUniformLocation(program, changeMatrixString);
			
			GLES20.glEnable(GLES20.GL_BLEND);
			GLES20.glBlendFunc(GLES20.GL_SRC_ALPHA, GLES20.GL_ONE_MINUS_SRC_ALPHA);
			
			Log.v(CutActivity.TAG, "program: " + program);
			
			//深度缓存,确保当前片断确实比先前画的片断更近
//			GLES20.glEnable(GLES20.GL_DEPTH_TEST);
//			GLES20.glDepthFunc(GLES20.GL_LESS);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private static final String vertexShaderString = 
			"uniform mat4 " + matrixString + ";" +
			"uniform mat4 " + changeMatrixString + ";" +
			"attribute vec4 " + vertexString + ";" +
		    "attribute vec2 " + textureCoordinatesString + ";" +
		    "varying vec2 v_TextureCoordinates;" +
		    "varying vec4 v_originalPosition;" +
		    "varying vec4 v_changedPosition;" +
		    "void main() {" +
		    "  v_originalPosition = " + vertexString + ";" +
		    "  v_TextureCoordinates = " + textureCoordinatesString + ";" +
		    "  gl_Position = " + matrixString + " * " + vertexString + ";" +
		    "  v_changedPosition = " + changeMatrixString + " * " + vertexString + ";" +
		    "  gl_PointSize = 10.0;" +
		    "}";
	
	private static final String fragmentShaderString = 
		    "precision mediump float;" +
		    "uniform sampler2D " + textureUnitString + ";" +
		    "uniform vec4 " + colorString + ";" +
		    "uniform float " + alphaString + ";" +
		    "uniform vec4 " + inVec4String + ";" +
		    "uniform vec4 " + showVec4String + ";" +
		    "varying vec2 v_TextureCoordinates;" +
		    "varying vec4 v_originalPosition;" +
		    "varying vec4 v_changedPosition;" +
		    "void main() {" +
		    "  if((v_changedPosition.x >= " + showVec4String+".x - " + showVec4String + ".z)" +
		    "  && (v_changedPosition.x <= " + showVec4String+".x + " + showVec4String + ".z)" +
		    "  && (v_changedPosition.y >= " + showVec4String+".y - " + showVec4String + ".w)" +
		    "  && (v_changedPosition.y <= " + showVec4String+".y + " + showVec4String + ".w)" +
		    "  ) {" +
		    "    gl_FragColor = texture2D(" + textureUnitString + ", v_TextureCoordinates) + " + colorString + ";" +
		    "  if((" + colorString + ".w != 0.0)) " +
		    "    gl_FragColor.a = " + colorString + ".w;" +
		    "  if((gl_FragColor.a != 0.0) " +
		    "  && (v_originalPosition.x >= " + inVec4String+".x - " + inVec4String + ".z)" +
		    "  && (v_originalPosition.x <= " + inVec4String+".x + " + inVec4String + ".z)" +
		    "  && (v_originalPosition.y >= " + inVec4String+".y - " + inVec4String + ".w)" +
		    "  && (v_originalPosition.y <= " + inVec4String+".y + " + inVec4String + ".w)" +
		    "  )" +
		    "    gl_FragColor.a = " + alphaString + ";" +
		    "  }" + 
		    "}";

}
