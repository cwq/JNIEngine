package com.cwq.object;

import java.util.ArrayList;
import java.util.List;

import com.cwq.opengl.OpenglESProgram;

public class MultiObject extends BaseObject {
	
	private List<BaseObject> objects;
	
	public MultiObject() {
		centerX = 0;
		centerY = 0;
		objects = new ArrayList<BaseObject>();
	}
	
	@Override
	public void setAlphaBy(float deta) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.setAlphaBy(deta);
		}
	}
	
	@Override
	public void setAlphaTo(float alpha) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.setAlphaTo(alpha);
		}
	}
	
	@Override
	public void setColor(float r, float g, float b, float a) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.setColor(r, g, b, a);
		}
	}
	
	@Override
	public void moveTo(float x, float y) {
		// TODO Auto-generated method stub
		moveBy(x - centerX, y - centerY);
	}
	
	@Override
	public void moveBy(float dx, float dy) {
		// TODO Auto-generated method stub
		centerX += dx;
		centerY += dy;
		for (BaseObject object : objects) {
			object.moveBy(dx, dy);
		}
	}
	
	@Override
	public void rotateBy(float angle, float x, float y, float z) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.rotateBy(angle, x, y, z);
		}
	}
	
	@Override
	public void rotateTo(float[] rotateMatrix) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.rotateTo(rotateMatrix);
		}
	}
	
	@Override
	public void scaleBy(float scaleX, float scaleY) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.scaleBy(scaleX, scaleY);
		}
	}
	
	@Override
	public void scaleTo(float scaleX, float scaleY) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.scaleTo(scaleX, scaleY);
		}
	}
	
	public void addObject(BaseObject object) {
		objects.add(object);
	}

	@Override
	public void draw(OpenglESProgram openglESProgram, double sElapsed) {
		// TODO Auto-generated method stub
		doAnimation(sElapsed);
		for (BaseObject object : objects) {
			object.draw(openglESProgram, sElapsed);
		}
	}

	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			if (object.isInObject(x, y)) {
				return true;
			}
		}
		return false;
	}
	
	@Override
	public void addTextureToManager() {
		// TODO Auto-generated method stub
		for (BaseObject object : objects) {
			object.addTextureToManager();
		}
	}

}
