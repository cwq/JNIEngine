package com.cwq.opengl;

import com.cwq.scene.Scene;

import android.content.res.AssetManager;

/**
 * 必须在opengles线程中使用
 * @author meitu
 *
 */
public class JNIOpenglESHelper {
	
	public static int createTexture(String fileName) {
		return createTexture(Scene.getMContext().getAssets(), fileName);
	}
	
	public static native int createTexture(AssetManager ass, String fileName);
	
	public static native void deleteTextures(int n, int[] textures);

}
