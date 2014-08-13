package com.cwq.opengl;

import com.cwq.engine.CutActivity;
import com.cwq.scene.Scene;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.util.Log;

/**
 * 必须在opengles线程中使用
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
			//GL_NEAREST 直接提取位于(U,V)坐标的纹素
			//GL_LINEAR 线性滤波,会查看周围的纹素，然后根据UV坐标距离各纹素中心的距离来混合颜色。这就避免了前面看到的锯齿状边缘
			//MIPMAP 把图像缩小到原来的1/2，接着一次做下去，直到图像只有1×1大小（应该是图像所有纹素的平均值）
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
