package com.sdk.mgr;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import android.os.Handler;
import android.os.Message;

public class utility {
	public static Handler handler = null;
	
	/*
	 * java调c++
	 */
	public static native void callEventToLua(final String eventType, final String response, final String token);
	public static native void setPlatformId(final int platformId);
	
	/*
	 * c++调java
	 */
	public static void EventTracking(String eventType, String params) {
		LogManager.d("cxx:EventTracking", "eventType = " + eventType + " params = "
				+ params);
		
		if (eventType == null || eventType.equals("")) {
			LogManager.e("cxx:EventTracking", "eventType error !");
			return;
		}
		Message msg = new Message();
		msg.what = Integer.parseInt(eventType);
		msg.obj = params;
		handler.sendMessage(msg);
	}
	
	/*
	 * CocosUI线程(runOnGLThread)
	 */
    public static void runNativeCallback(final String eventType, final String response, final String token)
    {
          Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
              @Override
              public void run() {
            	  callEventToLua(eventType, response, token);
              }
          });
     }
}
