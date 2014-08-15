package com.cwq.scene;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.cwq.engine.CutActivity;
import com.cwq.engine.AnimationActivity;
import com.cwq.jni.JNILib;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.SurfaceHolder;

public class Scene extends GLSurfaceView {
	
	private static Context mContext;
	public static Context getMContext() {
		return mContext;
	}

	public Scene(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		setEGLContextClientVersion(2);
		this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		mContext = context;
		
		JNILib.initAssetManager(context.getAssets());

		super.setRenderer(new SceneRenderer());
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		super.surfaceDestroyed(holder);
	}
	
	int framesPerSecond = 0;
	long lastTimeFrame = 0;
	long lastTime = 0;
	static final double NANO_SECOND = 1e9;
	
	class SceneRenderer implements Renderer {

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// TODO Auto-generated method stub
			Log.v(CutActivity.TAG, "onSurfaceCreated");
			
			JNILib.onSurfaceCreated();
			
			lastTime = lastTimeFrame = System.nanoTime();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			//在onSurfaceCreated 之后
			// TODO Auto-generated method stub
			Log.v(CutActivity.TAG, "onSurfaceChanged");
			
			JNILib.onSurfaceChanged(width, height);
		}

		@Override
		public void onDrawFrame(GL10 gl) {
			// TODO Auto-generated method stub
			long curTime = System.nanoTime();
			
			//draw
			JNILib.onDrawFrame();
			
			lastTime = curTime;
			
			framesPerSecond++;
			if (curTime - lastTimeFrame > NANO_SECOND) {
				Log.v(AnimationActivity.TAG, framesPerSecond + "");
				framesPerSecond = 0;
				lastTimeFrame = curTime;
			}
		}
		
	}
	
	@Override
	public void setRenderer(Renderer renderer) {
		// TODO Auto-generated method stub
		
	}

}
