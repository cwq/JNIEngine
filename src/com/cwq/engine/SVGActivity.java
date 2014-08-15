package com.cwq.engine;

import com.cwq.scene.Scene;

import android.app.Activity;
import android.os.Bundle;

public class SVGActivity extends Activity {
	
	public static final String TAG = "SVGActivity";
	private Scene myScene;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		myScene = new Scene(this);
		setContentView(myScene);
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
