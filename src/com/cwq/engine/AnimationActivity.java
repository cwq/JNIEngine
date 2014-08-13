package com.cwq.engine;

import java.util.ArrayList;
import java.util.List;

import com.cwq.animation.BaseAnimation;
import com.cwq.animation.ComplexAnimation;
import com.cwq.animation.FadeAnimation;
import com.cwq.animation.MoveAnimation;
import com.cwq.animation.RotateAnimation;
import com.cwq.animation.ScaleAnimation;
import com.cwq.animation.TintAnimation;
import com.cwq.object.RectangleTexture;
import com.cwq.scene.Scene;

import android.os.Bundle;
import android.app.Activity;
import android.graphics.PointF;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;

public class AnimationActivity extends Activity {
	
	public static final String TAG = "Engine";
	
	private List<BaseAnimation> animations;
	
	private Scene myScene;
	private RectangleTexture rectangleTexture;
	private int curAnimation = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		animations = new ArrayList<BaseAnimation>();
		myScene = new Scene(this);
		setContentView(myScene);
		
		rectangleTexture = new RectangleTexture(0.0f, 0.0f, 1.0f, 1.0f, R.drawable.first);
		myScene.addObj(rectangleTexture);
		
		init();
		
		//此处开始创建Button  
        LinearLayout ll = new LinearLayout(this);  
        ll.setOrientation(LinearLayout.VERTICAL);  
  
        Button lastButton = new Button(this);  
        lastButton.setText("last");  
        ll.addView(lastButton);  
        
        Button nextButton = new Button(this);  
        nextButton.setText("next");  
        ll.addView(nextButton);
        
        addContentView(ll, new LayoutParams(LayoutParams.WRAP_CONTENT,  
                LayoutParams.WRAP_CONTENT));  
        
        lastButton.setOnClickListener(new Button.OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                // TODO Auto-generated method stub  
            	if (curAnimation > 0) {
        			curAnimation = (curAnimation - 1) % animations.size();
        			rectangleTexture.setAnimation(animations.get(curAnimation));
            	}
            }  
        });  
        nextButton.setOnClickListener(new Button.OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                // TODO Auto-generated method stub  
            	curAnimation = (curAnimation + 1) % animations.size();
            	rectangleTexture.setAnimation(animations.get(curAnimation));
            }  
        }); 
	}
	
	private void init() {
		PointF startF = new PointF(rectangleTexture.getCenterX(), rectangleTexture.getCenterY());
//		BaseAnimation circleAnimation = MoveAnimation.circle(2.0f, 
//				startF, new PointF(0, 0), 0.5f);
//		circleAnimation.setRevert(true);
//		
//		BaseAnimation bezierAnimation = MoveAnimation.bezier(2.0f, startF,
//				new PointF(-1, 1), new PointF(1, 1), new PointF(1, 0));
//		bezierAnimation.setRevert(true);
		
		BaseAnimation fadeOut = FadeAnimation.fade(2.0f, 1, 0);
		fadeOut.setRevert(true);
		
		BaseAnimation fadeIn = FadeAnimation.fade(2.0f, 0, 1);
		
		BaseAnimation rotateAnimation = RotateAnimation.rotate(2.0f, rectangleTexture.getRotateMatrix(),
				360, 1, 1, 1);
		rotateAnimation.setRevert(true);
		
		BaseAnimation tint = TintAnimation.tint(2.0f, rectangleTexture.getColor(), 0, 1, 0, 1);
		tint.setRevert(true);
		
		BaseAnimation scaleS = ScaleAnimation.scaleTo(2.0f, rectangleTexture.getScaleX(), 0,
				rectangleTexture.getScaleY(), 0);
		scaleS.setRevert(true);
		
		BaseAnimation scaleB = ScaleAnimation.scaleTo(2.0f, 0, 1,
				0, 1);
		
		ComplexAnimation c1 = new ComplexAnimation(2.0f);
		c1.setRevert(true);
		c1.addAnimation(scaleS);
		c1.addAnimation(fadeOut);
		c1.addAnimation(rotateAnimation);
		animations.add(c1);
		
		ComplexAnimation c2 = new ComplexAnimation(2.0f);
		c2.setRevert(false);
		c2.addAnimation(scaleB);
		c2.addAnimation(fadeIn);
		c2.addAnimation(rotateAnimation);
		animations.add(c2);
		
		ComplexAnimation c3 = new ComplexAnimation(2.0f);
		c3.setRevert(true);
//		c3.addAnimation(circleAnimation);
		c3.addAnimation(tint);
		c3.addAnimation(rotateAnimation);
		animations.add(c3);
		
		
		animations.add(scaleB);
		animations.add(scaleS);
		animations.add(tint);
//		animations.add(circleAnimation);
//		animations.add(bezierAnimation);
		animations.add(fadeIn);
		animations.add(fadeOut);
		animations.add(rotateAnimation);
		
		curAnimation = 0;
		rectangleTexture.setAnimation(animations.get(curAnimation));
	}

	
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		myScene.onPause();
	}
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		myScene.onResume();
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
