package com.cwq.opengl;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;

import com.cwq.engine.CutActivity;

import android.util.Log;

public class TextureManager {
	
	private static boolean isClear = false;
	
	private static HashMap<String, Integer> textures = new HashMap<String, Integer>();
	
	public static synchronized void addTexture(String bitmapID) {
		if (!textures.containsKey(bitmapID)) {
			textures.put(bitmapID, -1);
		}
	}
	
	public static synchronized int getTextureID(String bitmapID) {
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
		clearTecture();
		Iterator<Entry<String, Integer>> iterator = textures.entrySet().iterator();
		while (iterator.hasNext()) {
			Entry<String, Integer> entry = iterator.next();
			if (entry.getValue() == -1) {
				try {
					textures.put(entry.getKey(), JNIOpenglESHelper.createTexture(entry.getKey()));
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
		clearTecture();
		Iterator<Entry<String, Integer>> iterator = textures.entrySet().iterator();
		while (iterator.hasNext()) {
			Entry<String, Integer> entry = iterator.next();
			try {
				textures.put(entry.getKey(), JNIOpenglESHelper.createTexture(entry.getKey()));
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	private static synchronized void clearTecture() {
		if (isClear) {
			Iterator<Entry<String, Integer>> iterator = textures.entrySet().iterator();
			int[] texs = new int[textures.size()];
			int num = 0;
			int texture = 0;
			while (iterator.hasNext()) {
				Entry<String, Integer> entry = iterator.next();
				texture = entry.getValue();
				if (texture != 0) {
					texs[num] = texture;
					num++;
				}
			}
			Log.v(CutActivity.TAG, "clear " + num);
			JNIOpenglESHelper.deleteTextures(num, texs);
			textures.clear();
			isClear = false;
		}
	}

	public static boolean isClear() {
		return isClear;
	}

	public static void setClear(boolean isClear) {
		TextureManager.isClear = isClear;
	}

}
