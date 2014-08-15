package com.cwq.jni;

import android.content.res.AssetManager;

public class JNILib {
	static {
        System.loadLibrary("JNIEngine");
    }
	
	 public static native void initAssetManager(AssetManager ass);
	 public static native void onSurfaceCreated();
	 public static native void onSurfaceChanged(int width, int height);
	 public static native void onDrawFrame();
}
