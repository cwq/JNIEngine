package com.cwq.engine;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	
	private Button animationButton;
	private Button cutButton;
	private Button svgButton;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		animationButton = (Button) findViewById(R.id.button1);
		animationButton.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(MainActivity.this, AnimationActivity.class);
				startActivity(intent);
			}
		});
		
		cutButton = (Button) findViewById(R.id.button2);
		cutButton.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(MainActivity.this, CutActivity.class);
				startActivity(intent);
			}
		});
		
		svgButton = (Button) findViewById(R.id.button3);
		svgButton.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(MainActivity.this, SVGActivity.class);
				startActivity(intent);
			}
		});
	}
}
