package com.cwq.object;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import com.cwq.opengl.OpenglESProgram;
import com.cwq.opengl.TextureManager;
import com.cwq.scene.Scene;

public class RectangleTexture extends TextureObject {
	
	protected float halfW;
	protected float halfH;
	
	private float startU = 0;
	private float startV = 0;
	private float endU = 1;
	private float endV = 1;
	
	private final float BASE_L = 0.8f;
	
	public RectangleTexture(int bitmapID) {
		this(bitmapID, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	public RectangleTexture(int bitmapID, float startU, float startV, float endU, float endV) {
		setWH(bitmapID, startU, startV, endU, endV);
		init(0, 0, halfW * 2, halfH * 2, bitmapID, startU, startV, endU, endV);
	}
	
	private void setWH(int bitmapID, float startU, float startV, float endU, float endV) {
		BitmapFactory.Options options = new BitmapFactory.Options();
		options.inScaled = false;
		Bitmap bitmap = BitmapFactory.decodeResource(Scene.getMContext().getResources(), bitmapID, options);
		
		halfW = halfH = BASE_L;
		if (bitmapID != NO_BITMAP && bitmap != null) {
			float scale = (bitmap.getWidth() * (endU - startU)) / (bitmap.getHeight() * (endV - startV));
			if (scale > 1) {
				halfH = halfW / scale;
			} else {
				halfW = halfH * scale;
			}
			bitmap.recycle();
		}
	}
	
	public RectangleTexture(float centerX, float centerY, float w, float h, int bitmapID) {
		this(centerX, centerY, w, h, bitmapID, 0, 0, 1, 1);
	}
	
	public RectangleTexture(float centerX, float centerY, float w, float h, int bitmapID,
			float startU, float startV, float endU, float endV) {
		init(centerX, centerY, w, h, bitmapID, startU, startV, endU, endV);
	}
	
	private void init(float centerX, float centerY, float w, float h, int bitmapID,
			float startU, float startV, float endU, float endV) {
		this.startU = startU;
		this.startV = startV;
		this.endU = endU;
		this.endV = endV;
		this.bitmapID = bitmapID;
		setAttribute(centerX, centerY, w, h, startU, startV, endU, endV);
		setGLBuffer();
	}
	
	private void setAttribute(float centerX, float centerY, float w, float h,
			float startU, float startV, float endU, float endV) {
		halfW = w / 2;
		halfH = h / 2;
		float[] attrib = {
				-halfW, halfH, 0.0f, startU, startV,
				-halfW, -halfH, 0.0f, startU, endV,
				halfW, -halfH, 0.0f, endU, endV,
				halfW, -halfH, 0.0f, endU, endV,
				halfW, halfH, 0.0f, endU, startV,
				-halfW, halfH, 0.0f, startU, startV
		};
		attribute = attrib;
		moveTo(centerX, centerY);
		setInVec4(0, 0, halfW, halfH);
	}

	@Override
	public void draw(OpenglESProgram openglESProgram, double sElapsed) {
		// TODO Auto-generated method stub
		if (bitmapID != NO_BITMAP) {
			setTextureID(TextureManager.getTextureID(bitmapID));
		}
		super.draw(openglESProgram, sElapsed);
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		return x >= centerX-halfW && x <= centerX+halfW &&
				y >= centerY-halfH && y <= centerY+halfH;
	}
	
	public float getHalfW() {
		return halfW;
	}

	public float getHalfH() {
		return halfH;
	}

	public float getStartU() {
		return startU;
	}

	public float getStartV() {
		return startV;
	}

	public float getEndU() {
		return endU;
	}

	public float getEndV() {
		return endV;
	}
}
