package com.cwq.opengl;

import com.cwq.engine.CutActivity;
import com.cwq.scene.Scene;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.util.Log;

/**
 * ������opengles�߳���ʹ��
 * @author meitu
 *
 */
public class OpenglESHelper {
	
	static int loadShader(int type, String shaderSource) throws Exception {
		int shader = GLES20.glCreateShader(type);
		if (shader != 0) {
			GLES20.glShaderSource(shader, shaderSource);
			GLES20.glCompileShader(shader);
			int[] compileStatus = new int[1];
			GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);
			if (compileStatus[0] == 0) {
				GLES20.glDeleteShader(shader);
				throw new Exception("Could not compile shader: " + GLES20.glGetShaderInfoLog(shader));
			}
		} else {
			throw new Exception("error occurs creating the shader");
		}
		return shader;
	}
	
	static int createTexture(int bitmapID) throws Exception {
		BitmapFactory.Options options = new BitmapFactory.Options();
		options.inScaled = false;
		Bitmap bitmap = BitmapFactory.decodeResource(Scene.getMContext().getResources(), bitmapID, options);
		if (bitmap == null) {
			Log.v(CutActivity.TAG, "null bitmap");
			return 0;
		}
		int[] textureObjectIds = new int[1];
		GLES20.glGenTextures(1, textureObjectIds, 0);
		if (textureObjectIds[0] != 0) {
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureObjectIds[0]);
			//GL_NEAREST ֱ����ȡλ��(U,V)���������
			//GL_LINEAR �����˲�,��鿴��Χ�����أ�Ȼ�����UV���������������ĵľ����������ɫ����ͱ�����ǰ�濴���ľ��״��Ե
			//MIPMAP ��ͼ����С��ԭ����1/2������һ������ȥ��ֱ��ͼ��ֻ��1��1��С��Ӧ����ͼ���������ص�ƽ��ֵ��
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR_MIPMAP_LINEAR);
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
			GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
			
			bitmap.recycle();
			
			GLES20.glGenerateMipmap(GLES20.GL_TEXTURE_2D);
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
		} else {
			throw new Exception("error occurs generate texture");
		}
		Log.v(CutActivity.TAG, "texture: " + textureObjectIds[0]);
		return textureObjectIds[0];
	}

}
