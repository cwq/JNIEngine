package com.cwq.jni;

import android.content.res.AssetManager;

public class JNILib {
	static {
//		System.loadLibrary("stlport_shared");
        System.loadLibrary("JNIEngine");
    }
	
	 public static native void initAssetManager(AssetManager ass);
	 public static native void onSurfaceCreated();
	 public static native void onSurfaceChanged(int width, int height);
	 public static native void onDrawFrame();
	 
	 public static native void onTouch(int type, float x, float y);
	 public static native void clickCut();
	 public static native void clickReset();
}
