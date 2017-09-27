package com.sdk.mgr;

import android.util.Log;

public class LogManager {
	public static Boolean isDevMode = false;

	public static void d(String tag, String msg) {
		if (isDevMode)
			Log.d(tag, msg);
	}

	public static void e(String tag, String msg){
		if (isDevMode)
			Log.e(tag, msg);
	}
}
