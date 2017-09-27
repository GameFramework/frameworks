package com.game456.lytl.havescreen;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.ImageView;

public class SplashActivity extends Activity {
	ImageView imageview;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.splash);
		
		imageview = (ImageView)this.findViewById(R.id.imageview);
		handler.sendEmptyMessageDelayed(0, 2000);
	}
	
	@SuppressLint("HandlerLeak")
	Handler handler = new Handler(){
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case 0:
				Intent intent = new Intent(SplashActivity.this, AppActivity.class);
				startActivityForResult(intent, 10);
				finish();
				break;
			default:
				break;
			}
		};
	};
}
