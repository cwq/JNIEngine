package com.cwq.opengl;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

import com.cwq.engine.CutActivity;

import android.opengl.GLES20;
import android.util.Log;

public class TextureManager {
	
	private static HashMap<Integer, Integer> textures = new HashMap<Integer, Integer>();
	
	public static synchronized void addTexture(int bitmapID) {
		if (!textures.containsKey(bitmapID)) {
			textures.put(bitmapID, -1);
		}
	}
	
	public static int getTextureID(int bitmapID) {
		Integer texture = textures.get(bitmapID);
		if (texture == null) {
			texture = 0;
		}
		return texture;
	}
	
	/**
	 * 加载还未加载的纹理
	 */
	public static synchronized void loadTextures() {
		Iterator<Entry<Integer, Integer>> iterator = textures.entrySet().iterator();
		while (iterator.hasNext()) {
			Entry<Integer, Integer> entry = iterator.next();
			if (entry.getValue() == -1) {
				try {
					textures.put(entry.getKey(), OpenglESHelper.createTexture(entry.getKey()));
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
	
	/**
	 * 重新加载所有纹理
	 */
	public static synchronized void reloadTextures() {
		Iterator<Entry<Integer, Integer>> iterator = textures.entrySet().iterator();
		while (iterator.hasNext()) {
			Entry<Integer, Integer> entry = iterator.next();
			try {
				textures.put(entry.getKey(), OpenglESHelper.createTexture(entry.getKey()));
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static synchronized void clearTecture() {
		Iterator<Entry<Integer, Integer>> iterator = textures.entrySet().iterator();
		int[] texs = new int[textures.size()];
		int num = 0;
		int texture = 0;
		while (iterator.hasNext()) {
			Entry<Integer, Integer> entry = iterator.next();
			texture = entry.getKey();
			if (texture != 0) {
				texs[num] = texture;
				num++;
			}
		}
		Log.v(CutActivity.TAG, "clear " + num);
		GLES20.glDeleteTextures(num, texs, 0);
		textures.clear();
	}

}
