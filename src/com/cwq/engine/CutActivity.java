package com.cwq.engine;

import com.cwq.jni.JNILib;
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
					JNILib.onTouch(event.getAction(), normalizedX, normalizedY);
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
            	JNILib.clickCut();
            }  
        });  
        resetButton.setOnClickListener(new Button.OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                // TODO Auto-generated method stub  
            	JNILib.clickReset();
            }  
        }); 
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
