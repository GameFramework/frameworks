package com.sdk.mgr;

import org.json.JSONException;
import org.json.JSONObject;
import android.app.Activity;
import android.os.Bundle;
import android.os.Message;

import com.kxyx.KxyxSDK;
import com.kxyx.bean.PayStateBean;
import com.kxyx.bean.UserInfoBean;

import android.app.AlertDialog;
import android.content.DialogInterface;

public class SDKManager{
	public static Activity mActivity = null;
	public static SDKManager instance = null;
	public static KxyxSDK sdkInstance = null;
	public static AlertDialog mAlertDialog = null;
	/*
	 * 单例
	 */
	public static SDKManager getInstance(){
		if(instance == null){
			instance = new SDKManager();
		}
		return instance;
	}
	
	/*
	 * 初始化SDK
	 */
	public void initSdk(Activity activity, Bundle savedInstanceState) {
		mActivity = activity;
		utility.setPlatformId(149);
		
		sdkInstance = KxyxSDK.getInstance();
		sdkInstance.init(activity);
		
		//登录回调
		sdkInstance.setOnLoginListener(new KxyxSDK.onLoginListener()
        {
            @Override
            public void onSuccess(UserInfoBean userInfoBean)
            {
            	String userId = userInfoBean.getUsername();
            	LogManager.d("登录成功：", userId);
            	
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	clientJson.put("platId", 149);
	            	clientJson.put("uid", userId);
					utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }

            @Override
            public void onFail(String msg)
            {
            	LogManager.d("登录失败：", msg);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_FAIL);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
        });
		
		//支付回调
		sdkInstance.setOnPayListener(new KxyxSDK.onPayListener()
        {
            @Override
            public void onResponse(PayStateBean payStateBean)
            {
            	String state = payStateBean.getState();
            	if (state != "1")
            	{
            		LogManager.d("支付失败：", state);
            		return;
            	}
            	
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_PAY), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
        });
		
		//登出回调
		sdkInstance.setOnLogoutListener(new KxyxSDK.onLogoutListener()
        {
            @Override
            public void onResponse()
            {
            	LogManager.d("登出回调：", "成功");
                try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGOUT), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
        });
	}

	/*
	 * 处理客服端消息
	 */
	public static void onHandleMessage(Message msg) {
		switch (msg.what) {
		case SDKDefine.EVENT_INIT:
			init();
			break;
		case SDKDefine.EVENT_LOGIN:
			login();
			break;
		case SDKDefine.EVENT_LOGOUT:
			logout();
			break;
		case SDKDefine.EVENT_PAY:
			pay(msg.obj.toString());
			break;
		case SDKDefine.EVENT_ROLEINFO:
			roleinfo(msg.obj.toString());
			break;
		case SDKDefine.EVENT_ENTER:
			break;
		case SDKDefine.EVENT_UPLEVEL:
			playerUpLevel(msg.obj.toString());
			break;
		case SDKDefine.EVENT_SCORE:
			break;
		case SDKDefine.EVENT_EXIT:
			exit();
			break;
		case SDKDefine.EVENT_CUSTOM:
			break;
		}
	}
	
	public static void init(){
		LogManager.d("初始化：", "init======");
		try {
			JSONObject clientJson = new JSONObject();
			clientJson.put("result", SDKDefine.RESULT_SUCCESS);
			clientJson.put("platId", 149);
			utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void login() {
		LogManager.d("登入：", "login======");
		sdkInstance.login(mActivity);
	}

	public static void logout() {
		LogManager.d("登出：", "logout======");
	}
	
	public static void exit() {
		LogManager.d("退出：", "exit======");
		mAlertDialog = null;
		if(mActivity.isFinishing()){
			mAlertDialog = null;
			return;
		}
			
		try {
			mAlertDialog = new AlertDialog.Builder(mActivity)
			.setTitle("退出")
			.setMessage("确定要退出游戏吗？")
			.setNegativeButton("取消", new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					mAlertDialog = null;
				}
			})
			.setPositiveButton("确定", new DialogInterface.OnClickListener(){
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					mAlertDialog = null;
					mActivity.finish();			
					System.exit(0);
				}
			})
			.create();
			
			mAlertDialog.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void roleinfo(String params) {
		LogManager.d("创建角色：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverNo = json.optString("serverNo");       	//区服
			String serverName = json.optString("serverName");   	//服务器名称
			String roleName = json.optString("roleName"); 			//角色名称 
			String roleLv = json.optString("level");  				//等级
			String time = json.optString("time");
			sdkInstance.reportCreateRole(serverName, serverNo, time, roleName, roleLv);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void playerUpLevel(String params){
		LogManager.d("角色升级：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverNo = json.optString("serverNo");       	//区服
			String serverName = json.optString("serverName");   	//服务器名称
			String roleName = json.optString("roleName"); 			//角色名称 
			String roleLv = json.optString("level");  				//等级
			sdkInstance.reportUpgrade(serverName, serverNo, roleName, roleLv);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public static void pay(String params) {
		LogManager.d("支付订单：", params);
		try {
			JSONObject json = new JSONObject(params);
			String myOrderId = json.optString("myOrderId");   				//游戏订单号
			String productName = json.optString("productName");  			//商品名称
			int realPrice = json.optInt("productRealPrice") / 100; 			//实际价格
			String description = json.optString("description");  			//商品描述
			
			JSONObject jsonObject = json.getJSONObject("exs");
			String roleName = jsonObject.optString("UserRoleName"); 		//角色名称
			String serverName = jsonObject.optString("UserServerName"); 	//服务器名称
			String noticeUrl = jsonObject.optString("NoticeUrl"); 			//支付回调地址
			sdkInstance.pay(mActivity, String.valueOf(realPrice), productName, description, myOrderId, noticeUrl, serverName, roleName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}		
}
