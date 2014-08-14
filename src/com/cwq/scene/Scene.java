package com.cwq.scene;

import java.util.ArrayList;
import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.cwq.engine.CutActivity;
import com.cwq.engine.AnimationActivity;
import com.cwq.object.BaseObject;
import com.cwq.opengl.JNIOpenglESProgram;
import com.cwq.opengl.TextureManager;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.SurfaceHolder;

public class Scene extends GLSurfaceView {
	
	private static float HALF_W = 1;
	private static float HALF_H = 1;
	
	private static final int R_INDEX = 0;
	private static final int G_INDEX = 1;
	private static final int B_INDEX = 2;
	private static final int A_INDEX = 3;
	
	private static Context mContext;
	public static Context getMContext() {
		return mContext;
	}

	//按照zOrder从小到大 越大显示越前
	private List<BaseObject> objects;

	private float[] bgColor = {0.8f, 0.8f, 0.8f, 0.0f};   //a=0 透明， a=1 不透明

	public Scene(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		setEGLContextClientVersion(2);
		this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		mContext = context;
		objects = new ArrayList<BaseObject>();

		super.setRenderer(new SceneRenderer());
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		super.surfaceDestroyed(holder);
		clear();
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
			
			JNIOpenglESProgram.onSurfaceCreated();
			
			TextureManager.reloadTextures();
			
			lastTime = lastTimeFrame = System.nanoTime();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			//在onSurfaceCreated 之后
			// TODO Auto-generated method stub
			Log.v(CutActivity.TAG, "onSurfaceChanged");
			final float aspectRatio = width > height ?
					(float) width / (float) height :
					(float) height / (float) width;
			if (width > height) {
				HALF_W = aspectRatio;
				HALF_H = 1;
			} else {
				HALF_W =1;
				HALF_H = aspectRatio;
			}
			JNIOpenglESProgram.onSurfaceChanged(width, height);
		}

		@Override
		public void onDrawFrame(GL10 gl) {
			// TODO Auto-generated method stub
			long curTime = System.nanoTime();
			
			JNIOpenglESProgram.onDrawFrame();
			
			TextureManager.loadTextures();
			
			synchronized (objects) {
				for (BaseObject obj : objects) {
					obj.draw((curTime - lastTime) / NANO_SECOND);
				}
			}
			lastTime = curTime;
			
			framesPerSecond++;
			if (curTime - lastTimeFrame > NANO_SECOND) {
				Log.v(AnimationActivity.TAG, framesPerSecond + "");
				framesPerSecond = 0;
				lastTimeFrame = curTime;
			}
		}
		
	}

	public static float getHALF_W() {
		return HALF_W;
	}
	
	public static float getHALF_H() {
		return HALF_H;
	}
	
	@Override
	public void setRenderer(Renderer renderer) {
		// TODO Auto-generated method stub
		
	}
	
	public void setBgColor(float r, float g, float b, float alpha) {
		bgColor[R_INDEX] = r;
		bgColor[G_INDEX] = g;
		bgColor[B_INDEX] = b;
		bgColor[A_INDEX] = alpha;
	}
	
	public void addObj(BaseObject obj) {
		addObj(obj, 0);
	}
	
	public void addObj(BaseObject obj, int zOrder) {
		synchronized (objects) {
			if (!objects.contains(obj)) {
				obj.setzOrder(zOrder);
				int size = objects.size();
				int index;
				for(index = 0; index < size; index++) {
					if (zOrder < objects.get(index).getzOrder()) {
						break;
					}
				}
				objects.add(index, obj);
				obj.addTextureToManager();
			}
		}
	}
	
	public void removeObj(BaseObject obj) {
		synchronized (objects) {
			objects.remove(obj);
		}
	}
	
	public void clear() {
		synchronized (objects) {
			objects.clear();
		}
		TextureManager.setClear(true);
	}

}
