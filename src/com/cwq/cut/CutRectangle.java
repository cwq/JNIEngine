package com.cwq.cut;

import android.graphics.PointF;
import com.cwq.animation.BaseAnimation;
import com.cwq.animation.ComplexAnimation;
import com.cwq.animation.FadeAnimation;
import com.cwq.animation.MoveAnimation;
import com.cwq.animation.ScaleAnimation;
import com.cwq.animation.TintAnimation;
import com.cwq.object.BaseObject;
import com.cwq.object.MultiObject;
import com.cwq.object.RectangleTexture;
import com.cwq.scene.Scene;

public class CutRectangle extends MultiObject {
	
	private RectangleTexture topLeft;
	private RectangleTexture topRight;
	private RectangleTexture bottomLeft;
	private RectangleTexture bottomRight;
	
	private BaseObject select;
	
	private float halfWCut;
	private float halfHCut;
	
	private float HALF_W_BACK;
	private float HALF_H_BACK;
	
	private BaseAnimation downAnimation;
	private BaseAnimation upAnimation;
	
	private float lastCenterX;
	private float lastCenterY;
	
	private RectangleTexture upLayer;
	
	private final float EDGE_L = 0.12f;
	private final float BIG_TO = 1.3f;
	
	private final float LEAST_HALFW = EDGE_L;
	private final float LEAST_HALFH = EDGE_L;
	
	private final float ANIMATION_TIME = 0.3f;
	
	private RectangleTexture backRectTexture;
	
	public CutRectangle(int bitmapID, RectangleTexture backRectTexture, RectangleTexture upLayer) {
		topLeft = new RectangleTexture(0f, 0f, EDGE_L, EDGE_L, bitmapID);
		topLeft.setColor(0.8f, 0.8f, 0.8f, 0);
		topRight = new RectangleTexture(0f, 0f, EDGE_L, EDGE_L, bitmapID);
		topRight.setColor(0.8f, 0.8f, 0.8f, 0);
		bottomLeft = new RectangleTexture(0f, -0f, EDGE_L, EDGE_L, bitmapID);
		bottomLeft.setColor(0.8f, 0.8f, 0.8f, 0);
		bottomRight = new RectangleTexture(0f, 0f, EDGE_L, EDGE_L, bitmapID);
		bottomRight.setColor(0.8f, 0.8f, 0.8f, 0);
		
		addObject(topLeft);
		addObject(topRight);
		addObject(bottomLeft);
		addObject(bottomRight);
		
		downAnimation = ScaleAnimation.scaleTo(ANIMATION_TIME, 1, BIG_TO, 1, BIG_TO);
		upAnimation = ScaleAnimation.scaleTo(ANIMATION_TIME, BIG_TO, 1, BIG_TO, 1);
		
		setBackRect(backRectTexture, upLayer, false);
	}
	
	/**
	 * 
	 * @param backRectTexture
	 * @param upLayer
	 * @param isFull 裁剪框是否占满背景
	 */
	public void setBackRect(RectangleTexture backRectTexture, RectangleTexture upLayer, boolean isFull) {
		this.upLayer = upLayer;
		this.backRectTexture = backRectTexture;
		centerX = 0;
		centerY = 0;
		halfWCut = HALF_W_BACK = backRectTexture.getHalfW();
		halfHCut = HALF_H_BACK = backRectTexture.getHalfH();
		if (!isFull) {
			halfWCut *= 0.5;
			halfHCut *= 0.5;
		}
		
		topLeft.moveTo(centerX - halfWCut, centerY + halfHCut);
		topRight.moveTo(centerX + halfWCut, centerY + halfHCut);
		bottomLeft.moveTo(centerX -halfWCut, centerY - halfHCut);
		bottomRight.moveTo(centerX + halfWCut, centerY - halfHCut);
		
		upLayer.setAlphaTo(0);
		upLayer.setColor(0, 0, 0, 0);
		upLayer.setAnimation(TintAnimation.tint(ANIMATION_TIME, upLayer.getColor(), 0, 0, 0, 0.5f));
		updateUpLayer();
		
		if (!isFull) {
			ComplexAnimation inAnimation = new ComplexAnimation(ANIMATION_TIME);
			inAnimation.addAnimation(FadeAnimation.fade(ANIMATION_TIME, 0, 1));
			inAnimation.addAnimation(ScaleAnimation.scaleTo(ANIMATION_TIME, 0.2f, 1, 0.2f, 1));
			this.setAnimation(inAnimation);
		}
	}
	
	public void setBackRect(RectangleTexture backRectTexture, RectangleTexture upLayer) {
		setBackRect(backRectTexture, upLayer, true);
	}
	
	private void updateUpLayer() {
		upLayer.setInVec4(centerX, centerY, halfWCut, halfHCut);
	}
	
	public void doCutAnimation(Scene myScene, RectangleTexture tempTexture, RectangleTexture finalTexture) {
		//裁剪的小图拉伸动画
		ComplexAnimation changeAnimation = new ComplexAnimation(ANIMATION_TIME);
    	changeAnimation.addAnimation(MoveAnimation.moveTo(ANIMATION_TIME, 
    			new PointF(tempTexture.getCenterX(), tempTexture.getCenterY()), new PointF(0, 0)));
    	float scaleX = finalTexture.getHalfW() / tempTexture.getHalfW();
    	float scaleY = finalTexture.getHalfH() / tempTexture.getHalfH();
    	BaseAnimation scale = ScaleAnimation.scaleTo(ANIMATION_TIME, 1, scaleX, 1, scaleY);
    	changeAnimation.addAnimation(scale);
    	tempTexture.setAnimation(changeAnimation);
    	
//    	//背景淡出
//    	backRectTexture.setAnimation(FadeAnimation.fade(ANIMATION_TIME, 1, 0));
//    	upLayer.setInVec4(0, 0, HALF_W_BACK, HALF_H_BACK);
//    	upLayer.setAnimation(FadeAnimation.fade(ANIMATION_TIME, 0.5f, 0));
    	
    	//设置显示范围，使放大在一定范围内
    	float halfW = backRectTexture.getHalfW() > finalTexture.getHalfW() ? backRectTexture.getHalfW() : finalTexture.getHalfW();
		float halfH = backRectTexture.getHalfH() > finalTexture.getHalfH() ? backRectTexture.getHalfH() : finalTexture.getHalfH();
		backRectTexture.setShowVec4(0, 0, halfW, halfH);
		upLayer.setShowVec4(0, 0, halfW, halfH);
		
		//背景图和蒙层拉伸动画
    	ComplexAnimation back = new ComplexAnimation(ANIMATION_TIME);
    	back.addAnimation(MoveAnimation.moveTo(ANIMATION_TIME, new PointF(0, 0),
    			new PointF(-tempTexture.getCenterX() * scaleX, -tempTexture.getCenterY()*scaleY)));
    	back.addAnimation(scale);
    	backRectTexture.setAnimation(back);
    	upLayer.setInVec4(0, 0, 0, 0);
    	upLayer.setAnimation(back);
    	
    	//裁剪框顶点移动动画
    	topLeft.setAnimation(MoveAnimation.moveTo(ANIMATION_TIME, 
    			new PointF(topLeft.getCenterX(), topLeft.getCenterY()),
    			new PointF(-finalTexture.getHalfW(), finalTexture.getHalfH())));
    	topRight.setAnimation(MoveAnimation.moveTo(ANIMATION_TIME, 
    			new PointF(topRight.getCenterX(), topRight.getCenterY()),
    			new PointF(finalTexture.getHalfW(), finalTexture.getHalfH())));
    	bottomLeft.setAnimation(MoveAnimation.moveTo(ANIMATION_TIME, 
    			new PointF(bottomLeft.getCenterX(), bottomLeft.getCenterY()),
    			new PointF(-finalTexture.getHalfW(), -finalTexture.getHalfH())));
    	bottomRight.setAnimation(MoveAnimation.moveTo(ANIMATION_TIME, 
    			new PointF(bottomRight.getCenterX(), bottomRight.getCenterY()),
    			new PointF(finalTexture.getHalfW(), -finalTexture.getHalfH())));
    	while(backRectTexture.isRunAnimation()) {
    		
    	}
    	
//    	//显示范围设置回
//    	backRectTexture.setShowVec4(0, 0, 10, 10);
//		upLayer.setShowVec4(0, 0, 10, 10);
	}
	
	/**
	 * 获取裁剪后的原始位置RectangleTexture
	 * @return
	 */
	public RectangleTexture getCutTempTexture() {
		float[] uv = getUV();
		return new RectangleTexture(centerX, centerY, halfWCut * 2, halfHCut * 2, 
				backRectTexture.getBitmapID(), uv[0], uv[1], uv[2], uv[3]);
	}
	
	/**
	 * 获取裁剪后最终应该显示的RectangleTexture
	 * @return
	 */
	public RectangleTexture getCutFinalTexture() {
		float[] uv = getUV();
		return new RectangleTexture(backRectTexture.getBitmapID(), uv[0], uv[1], uv[2], uv[3]);
	}
	
	private float[] getUV() {
		float scaleU = (backRectTexture.getEndU() - backRectTexture.getStartU()) / HALF_W_BACK / 2;
		float scaleV = (backRectTexture.getEndV() - backRectTexture.getStartV()) / HALF_H_BACK / 2;
		float startU = backRectTexture.getStartU() + (centerX + HALF_W_BACK - halfWCut) * scaleU;
		float startV = backRectTexture.getStartV() + (HALF_H_BACK - centerY  - halfHCut) * scaleV;
		float endU = backRectTexture.getStartU() + (centerX + HALF_W_BACK + halfWCut) * scaleU;
		float endV = backRectTexture.getStartV() + (HALF_H_BACK - centerY  + halfHCut) * scaleV;
		float[] uv =  {startU, startV, endU, endV};
		return uv;
	}
	
	@Override
	public boolean isInObject(float x, float y) {
		// TODO Auto-generated method stub
		if (topLeft.isInObject(x, y)) {
			select = topLeft;
			return true;
		}
		if (topRight.isInObject(x, y)) {
			select = topRight;
			return true;
		}
		if (bottomLeft.isInObject(x, y)) {
			select = bottomLeft;
			return true;
		}
		if (bottomRight.isInObject(x, y)) {
			select = bottomRight;
			return true;
		}
		if (isInCut(x, y)) {
			select = this;
			return true;
		}
		select = null;
		return false;
	}
	
	private boolean isInCut(float x, float y) {
		return x >= centerX-halfWCut && x <= centerX+halfWCut &&
				y >= centerY-halfHCut && y <= centerY+halfHCut;
	}
	
	public void touchMove(float dx, float dy) {
		if (select != null) {
			float x = lastCenterX + dx;
			float y = lastCenterY + dy;
			if (select == this) {
				//4个点都要在范围内  即  中心在 背景扣除裁剪框 的范围内
				if (x < -HALF_W_BACK + halfWCut) {
					x = -HALF_W_BACK + halfWCut;
				} else {
					if (x > HALF_W_BACK - halfWCut) {
						x = HALF_W_BACK - halfWCut;
					}
				}
				if (y < -HALF_H_BACK + halfHCut) {
					y = -HALF_H_BACK + halfHCut;
				} else {
					if (y > HALF_H_BACK - halfHCut) {
						y = HALF_H_BACK - halfHCut;
					}
				}
				select.moveTo(x, y);
			} else {
				if (x < -HALF_W_BACK) {
					x = -HALF_W_BACK;
				} else {
					if (x > HALF_W_BACK) {
						x = HALF_W_BACK;
					}
				}
				if (y < -HALF_H_BACK) {
					y = -HALF_H_BACK;
				} else {
					if (y > HALF_H_BACK) {
						y = HALF_H_BACK;
					}
				}
				moveVertex(x, y);
			}
			updateUpLayer();
		}
	}
	
	private void moveVertex(float x, float y) {
		if (select == topLeft) {
			if (x > centerX - LEAST_HALFW) {
				x = centerX - LEAST_HALFW;
			}
			if (y < centerY + LEAST_HALFH) {
				y = centerY + LEAST_HALFH;
			}
			topLeft.moveTo(x, y);
			topRight.moveTo(topRight.getCenterX(), y);
			bottomLeft.moveTo(x, bottomLeft.getCenterY());
		}
		else if (select == topRight) {
			if (x < centerX + LEAST_HALFW) {
				x = centerX + LEAST_HALFW;
			}
			if (y < centerY + LEAST_HALFH) {
				y = centerY + LEAST_HALFH;
			}
			topRight.moveTo(x, y);
			topLeft.moveTo(topLeft.getCenterX(), y);
			bottomRight.moveTo(x, bottomRight.getCenterY());
		}
		else if (select == bottomLeft) {
			if (x > centerX - LEAST_HALFW) {
				x = centerX - LEAST_HALFW;
			}
			if (y > centerY - LEAST_HALFH) {
				y = centerY - LEAST_HALFH;
			}
			bottomLeft.moveTo(x, y);
			topLeft.moveTo(x, topLeft.getCenterY());
			bottomRight.moveTo(bottomRight.getCenterX(), y);
		}
		else if (select == bottomRight) {
			if (x < centerX + LEAST_HALFW) {
				x = centerX + LEAST_HALFW;
			}
			if (y > centerY - LEAST_HALFH) {
				y = centerY - LEAST_HALFH;
			}
			bottomRight.moveTo(x, y);
			topRight.moveTo(x, topRight.getCenterY());
			bottomLeft.moveTo(bottomLeft.getCenterX(), y);
		}
		
		centerX = (topRight.getCenterX() + topLeft.getCenterX()) / 2;
		centerY = (topRight.getCenterY() + bottomRight.getCenterY()) / 2;
		halfWCut = (topRight.getCenterX() - topLeft.getCenterX()) / 2;
		halfHCut = (topRight.getCenterY() - bottomRight.getCenterY()) / 2;
	}
	
	public void touchDown(float x, float y) {
		isInObject(x, y);
		if (select != null) {
			select.setAnimation(downAnimation);
			lastCenterX = select.getCenterX();
			lastCenterY = select.getCenterY();
		}
	}
	
	public void touchUp() {
		if (select != null) {
			select.setAnimation(upAnimation);
			select = null;
		}
	}
}
