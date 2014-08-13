package com.cwq.animation;

import com.cwq.object.BaseObject;

import android.graphics.PointF;

public class MoveAnimation extends BaseAnimation {
	
	private PointF startPointF;
	private PointF endPointF;
	
	public MoveAnimation(float duration) {
		super(duration);
	}

	@Override
	void doAnimation(BaseObject object, float sElapsed) {
		// TODO Auto-generated method stub
		if (sElapsed <= sDuration) {
			object.moveTo(startPointF.x + (endPointF.x - startPointF.x) * sElapsed / sDuration,
					startPointF.y + (endPointF.y - startPointF.y) * sElapsed / sDuration);
		}
	}

	@Override
	void revert(BaseObject object) {
		// TODO Auto-generated method stub
		object.moveTo(startPointF.x, startPointF.y);
	}
	
	public PointF getStartPointF() {
		return startPointF;
	}

	public void setStartPointF(PointF startPointF) {
		this.startPointF = startPointF;
	}
	
	public PointF getEndPointF() {
		return endPointF;
	}

	public void setEndPointF(PointF endPointF) {
		this.endPointF = endPointF;
	}

	public static BaseAnimation moveTo(float duration, PointF start, PointF end) {
		MoveAnimation animation = new MoveAnimation(duration);
		animation.setStartPointF(start);
		animation.setEndPointF(end);
		return animation;
	}
	
//	public static BaseAnimation circle(float duration, PointF start, PointF center, float radius) {
//		int num = (int) (duration * FPS);
//		MoveAnimation animation = new MoveAnimation(duration);
//		animation.setStartPointF(start);
//		if (num > 1) {
//			double step = 2 * Math.PI / (num - 1);
//			for (double i = 0; i < 2 * Math.PI + step; i += step) {
//				PointF pointF = new PointF((float) Math.cos(i) * radius + center.x,
//						(float) Math.sin(i) * radius + center.y);
//				animation.addPoint(pointF);
//			}
//		}
//		return animation;
//	}
//	
//	public static BaseAnimation bezier(float duration, PointF start, PointF c1, PointF c2, PointF end) {
//		int num = (int) (duration * FPS);
//		MoveAnimation animation = new MoveAnimation(duration);
//		animation.setStartPointF(start);
//		if (num > 1) {
//			float dt = (float) (1.0 / (num -1));
//			for (int i = 0; i < num; i++) {
//				PointF pointF = new PointF();
//				float ax, bx, cx; float ay, by, cy; 
//				float tSquared, tCubed;
//				float t = i * dt;
//				/* 计算多项式系数 */ 
//				cx = (float) (3.0 * (c1.x - start.x)); 
//				bx = (float) (3.0 * (c2.x - c1.x) - cx); 
//				ax = end.x - start.x - cx - bx; 
//				cy = (float) (3.0 * (c1.y - start.y)); 
//				by = (float) (3.0 * (c2.y - c1.y) - cy); 
//				ay = end.y - start.y - cy - by; 
//				/* 计算t位置的点值 */ 
//				tSquared = t * t; 
//				tCubed = tSquared * t; 
//				pointF.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + start.x; 
//				pointF.y = (ay * tCubed) + (by * tSquared) + (cy * t) + start.y; 
//				animation.addPoint(pointF);
//			}
//		} else {
//			animation.addPoint(end);
//		}
//		
//		return animation;
//	}
//	
//	public static BaseAnimation complex(MoveAnimation a1, MoveAnimation a2) {
//		int num = a1.getTotalSteps() < a2.getTotalSteps() ? a1.getTotalSteps() : a2.getTotalSteps();
//		MoveAnimation animation = new MoveAnimation(num);
//		for (int i = 0; i < num; i++) {
//			animation.addPoint(new PointF(a1.getPointF(i).x + a2.getPointF(i).x, 
//					a1.getPointF(i).y + a2.getPointF(i).y));
//		}
//		return animation;
//	}

}
 