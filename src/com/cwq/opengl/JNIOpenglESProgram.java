package com.cwq.opengl;

public class JNIOpenglESProgram {
	
	public static native void onSurfaceCreated();
	
	public static native void onSurfaceChanged(int width, int height);
	
	public static native void onDrawFrame();

}
