package com.sdk.mgr;

import org.json.JSONException;
import org.json.JSONObject;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Message;

import com.vqs456.sdk.VqsManager;
import com.vqs456.sdk.http.LogOutListener;
import com.vqs456.sdk.http.LoginListener;
import com.vqs456.sdk.http.PayListener;

public class SDKManager{
	public static Activity mActivity = null;
	public static SDKManager instance = null;
	public static AlertDialog mAlertDialog = null;
	
	public static VqsManager vqsManager;
	private LoginListener loginListener;
	private PayListener payListener;
	private LogOutListener logOutListener;
	
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
		utility.setPlatformId(151);
		
		//初始化回调
		loginListener = new LoginListener() {
			@Override
			public void LoginSuccess(String result, String userID, String username, String logintime, String sign) {
				LogManager.d("登录成功：", userID + "||" + sign);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	clientJson.put("platId", 151);
	            	clientJson.put("uid", userID);
					utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), sign + "|" + logintime);
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
			}

			@Override
			public void LoginFailure(String errorID) {
				LogManager.d("登录失败：", errorID);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_FAIL);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
			}
		};
		
		payListener = new PayListener() {
			@Override
			public void PaySuccess(String result) {
				LogManager.d("支付成功", "====");
			}

			@Override
			public void PayFailure(String errorID) {
				LogManager.d("支付失败：", errorID);
			}

			@Override
			public void PayCancel(String errorID) {
				LogManager.d("支付取消：", errorID);
			}
		};
		
		logOutListener = new LogOutListener() {
			@Override
			public void LogOut(String result) {
				LogManager.d("登出回调：", "成功");
                try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGOUT), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
			}
		};
		
		//初始化sdk
		vqsManager = VqsManager.getInstance();
		vqsManager.init(mActivity, loginListener, payListener);
		//设置注销回调
		vqsManager.setLogOutListerner(logOutListener);
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
			enterGame(msg.obj.toString());
			break;
		case SDKDefine.EVENT_UPLEVEL:
			playerUpLevel(msg.obj.toString());
			break;
		case SDKDefine.EVENT_SCORE:
			setScore(msg.obj.toString());
			break;
		case SDKDefine.EVENT_EXIT:
			exit();
			break;
		case SDKDefine.EVENT_CUSTOM:
			break;
		}
	}
	
	public static void init(){
		LogManager.d("初始化:", "init======");
		try {
			JSONObject clientJson = new JSONObject();
			clientJson.put("result", SDKDefine.RESULT_SUCCESS);
			clientJson.put("platId", 151);
			utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void login() {
		LogManager.d("登入:", "login======");
		vqsManager.login();
	}

	public static void logout() {
		LogManager.d("登出:", "logout======");
		vqsManager.LogOut();
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
			String serverName = json.optString("serverName");   	//服务器名称
			String roleName = json.optString("roleName"); 			//角色名称
			String roleId = json.optString("roleId");  				//角色ID
			String level = json.optString("level");  				//等级
			vqsManager.setGameInfo(roleId, roleName, "战士", level, "", "0", "0", "蓝月屠龙", serverName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void enterGame(String params){
		LogManager.d("进入游戏：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			String roleId = json.optString("roleId");
			String level = json.optString("level");
			vqsManager.setGameInfo(roleId, roleName, "战士", level, "", "0", "0", "蓝月屠龙", serverName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void playerUpLevel(String params){
		LogManager.d("角色升级：", params);
	}
	
	public static void setScore(String params){
		LogManager.d("设置分数：", params);
	}

	public static void pay(String params) {
		LogManager.d("支付订单：", params);
		try {
			JSONObject json = new JSONObject(params);
			String myOrderId = json.optString("myOrderId");   				//游戏订单号
			String productName = json.optString("productName");  			//商品名称
			int realPrice = json.optInt("productRealPrice"); 				//实际价格
			vqsManager.Pay(String.valueOf(realPrice), productName, myOrderId, "0");
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
}