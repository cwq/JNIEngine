package com.cwq.engine;

import com.cwq.cut.CutRectangle;
import com.cwq.object.RectangleTexture;
import com.cwq.scene.Scene;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;

public class CutActivity extends Activity {
	
	public static final String TAG = "CutActivity";
	
	private Scene myScene;
	
	private RectangleTexture backRectTexture;
	private RectangleTexture firstBackRect;
	private RectangleTexture upLayer;
	private CutRectangle cutRect;
	
	private float downX;
	private float downY;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		Log.v(CutActivity.TAG, "onCreate");
		super.onCreate(savedInstanceState);
		myScene = new Scene(this);
		myScene.setOnTouchListener(new OnTouchListener() {
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				// TODO Auto-generated method stub
				if (event != null) {
					final float normalizedX;
					final float normalizedY;
					if (v.getHeight() > v.getWidth()) {
						normalizedX = (event.getX() / (float) v.getWidth()) * 2 - 1;
						normalizedY = -((event.getY() / (float) v.getHeight()) * 2 - 1) * v.getHeight() / v.getWidth();
					} else {
						normalizedX = ((event.getX() / (float) v.getWidth()) * 2 - 1) * v.getWidth() / v.getHeight();
						normalizedY = -((event.getY() / (float) v.getHeight()) * 2 - 1);
					}
					switch (event.getAction()) {
					case MotionEvent.ACTION_DOWN:
						cutRect.touchDown(normalizedX, normalizedY);
						downX = normalizedX;
						downY = normalizedY;
						break;
					case MotionEvent.ACTION_MOVE:
						cutRect.touchMove(normalizedX - downX, normalizedY - downY);
						break;
					case MotionEvent.ACTION_UP:
						cutRect.touchUp();
						break;
					default:
						break;
					}
					return true;
				}
				return false;
			}
		});
		setContentView(myScene);
		
		//此处开始创建Button  
        LinearLayout ll = new LinearLayout(this);  
        ll.setOrientation(LinearLayout.HORIZONTAL);  

        Button cutButton = new Button(this);  
        cutButton.setText("cut");  
        ll.addView(cutButton);  
        
        Button resetButton = new Button(this);  
        resetButton.setText("reset");  
        ll.addView(resetButton);
        
        addContentView(ll, new LayoutParams(LayoutParams.WRAP_CONTENT,  
                LayoutParams.WRAP_CONTENT));  
        
        cutButton.setOnClickListener(new Button.OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                // TODO Auto-generated method stub  
            	RectangleTexture tempTexture = cutRect.getCutTempTexture();
            	myScene.addObj(tempTexture, 25);
            	RectangleTexture finalTexture = cutRect.getCutFinalTexture();
            	cutRect.doCutAnimation(myScene, tempTexture, finalTexture);
            	myScene.removeObj(tempTexture);
            	setCut(finalTexture, true);
            }  
        });  
        resetButton.setOnClickListener(new Button.OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                // TODO Auto-generated method stub  
            	firstBackRect.setAlphaTo(1);
            	firstBackRect.scaleTo(1, 1);
            	firstBackRect.moveTo(0, 0);
            	setCut(firstBackRect, false);
            }  
        }); 
		
		firstBackRect = backRectTexture = new RectangleTexture(R.drawable.second);
		
		upLayer = new RectangleTexture(0.0f ,0.0f, backRectTexture.getHalfW() * 2,
				backRectTexture.getHalfH() * 2, -1);
		
		cutRect = new CutRectangle(R.drawable.cut, backRectTexture, upLayer);
		myScene.addObj(cutRect, 30);
		
		setCut(backRectTexture, false);
	}
	
	private void setCut(RectangleTexture back, boolean isFull) {
		myScene.removeObj(backRectTexture);
		myScene.removeObj(upLayer);
		
		backRectTexture = back;
		myScene.addObj(backRectTexture, 10);
		
		upLayer = new RectangleTexture(0.0f ,0.0f, backRectTexture.getHalfW() * 2,
				backRectTexture.getHalfH() * 2, -1);
		myScene.addObj(upLayer, 20);
		
		cutRect.setBackRect(backRectTexture, upLayer, isFull);
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

}
