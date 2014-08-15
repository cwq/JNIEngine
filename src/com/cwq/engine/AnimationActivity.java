package com.cwq.engine;

import com.cwq.scene.Scene;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class AnimationActivity extends Activity {
	
	public static final String TAG = "Engine";
	
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
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
