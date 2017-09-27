package com.sdk.mgr;

import org.json.JSONException;
import org.json.JSONObject;

import com.rsdk.framework.controller.ExitListener;
import com.rsdk.framework.controller.InitListener;
import com.rsdk.framework.controller.LoginListener;
import com.rsdk.framework.controller.PayListener;
import com.rsdk.framework.controller.consts.ToolBarConsts;
import com.rsdk.framework.controller.impl.RSDKPlatform;
import com.rsdk.framework.controller.info.AnalyticsInfo;
import com.rsdk.framework.controller.info.ProductInfo;
import com.rsdk.framework.controller.info.UserInfo;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Message;

public class SDKManager{
	public static Activity mActivity = null;
	public static SDKManager instance = null;
	public static AlertDialog mAlertDialog = null;
	public static int initStatus = 0;
	public static String APP_KEY = "c249a0-e5267-5587c-34688-549ffd72888";
	public static String APP_SECRET = "79175c06628dfb50850ad8fff7009a382795d323";
	public static String PRIVATE_KEY = "C7755A4EE5727B4FF71B55FC48303979";
	//支付统计
	public static String mRoleId = "1";
	public static String mRoleName = "1";
	public static String mRoleLevel = "1";
	public static String mVipLevel = "0";
	public static String mServerId = "1";
	public static String mServerName = "1";
	public static String mOrderId = "1";
	public static String mPrice = "1";
	public static String mCoinNum = "10";
	
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
		utility.setPlatformId(232);
		init();
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
			break;
		case SDKDefine.EVENT_EXIT:
			exit();
			break;
		case SDKDefine.EVENT_CUSTOM:
			custom(msg.obj.toString());
			break;
		}
	}
	
	public static void init(){
		LogManager.d("初始化:", "init======");
		if (initStatus == 1)
		{
			try {
    			JSONObject clientJson = new JSONObject();
    			clientJson.put("result", SDKDefine.RESULT_SUCCESS);
    			clientJson.put("platId", 232);
    			utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
    		} catch (JSONException e) {
    			e.printStackTrace();
    		}
			return;
		}
		
		if (initStatus > 0)
		{
			return;
		}
		
		initStatus = 2;
		RSDKPlatform.getInstance().init(mActivity, APP_KEY, APP_SECRET, PRIVATE_KEY, new InitListener() {
			@Override
            public void onInitSuccess(String msg) {
            	LogManager.d("初始化成功", "======");
            	initStatus = 1;
            	try {
        			JSONObject clientJson = new JSONObject();
        			clientJson.put("result", SDKDefine.RESULT_SUCCESS);
        			clientJson.put("platId", 232);
        			utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
        		} catch (JSONException e) {
        			e.printStackTrace();
        		}
            }
			
            @Override
            public void onInitFail(String msg) {
            	LogManager.d("初始化失败：", msg);
            	initStatus = 0;
            }
		});
	}
	
	public static void login() {
		LogManager.d("登入:", "login======");
		RSDKPlatform.getInstance().login("", new LoginListener() {
            @Override
            public void onLoginSuccess(UserInfo userInfo) {
            	String uid = userInfo.getUserId();
				String token = userInfo.getToken();
				String channelId = RSDKPlatform.getInstance().getSubAppId();
                LogManager.d("登录成功：", uid + "====" + token);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	clientJson.put("platId", 232);
	            	clientJson.put("channelId", channelId);
	            	clientJson.put("uid", uid + "|" + channelId);
					utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), token);
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            	
            	RSDKPlatform.getInstance().showToolBar(ToolBarConsts.LEFT_TOP);
            }
            
            @Override
            public void onLoginFail(String msg) {
                LogManager.d("登录失败：", msg);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_FAIL);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
            
            @Override
            public void onLoginCancel(String msg) {
                LogManager.d("登录取消：", msg);
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_FAIL);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
            
            @Override
            public void onAccountSwitchSuccess(String msg) {
            	LogManager.d("注销账号", "成功");
                try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", SDKDefine.RESULT_SUCCESS);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGOUT), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
            
            @Override
            public void onAccountSwitchFail(String msg) {
            	LogManager.d("注销账号", "失败");
            }
            
            @Override
            public void onAccountSwitchCancel(String msg) {
            	LogManager.d("注销账号", "取消");
            }
            
            @Override
            public void onAntiAddictionQueryNoCertification(String msg) {
            	LogManager.d("实名认证状态：", "未实名认证");
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", 1);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_CUSTOM), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
            
            @Override
            public void onAntiAddictionQueryNoAdult(String msg) {
            	LogManager.d("实名认证状态：", "未成年");
            	try {
	            	JSONObject clientJson = new JSONObject();
	            	clientJson.put("result", 2);
	            	utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_CUSTOM), clientJson.toString(), "");
            	} catch (JSONException e) {
            		e.printStackTrace();
        		}
            }
            
            @Override
            public void onAntiAddictionQueryAdult(String msg) {
            	LogManager.d("实名认证状态：", "已成年");
            }
        });
	}

	public static void logout() {
		LogManager.d("登出:", "logout======");
		RSDKPlatform.getInstance().hideToolBar();
		RSDKPlatform.getInstance().accountSwitch();
	}
	
	public static void exit() {
		LogManager.d("退出：", "exit======");
		RSDKPlatform.getInstance().exit(new ExitListener() {
			@Override
			public void onSdkExit() {
				mAlertDialog = null;
				mActivity.finish();			
				System.exit(0);
			}
			
			@Override
			public void onGameExit() {
				if(mActivity.isFinishing()){
					return;
				}
				
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
			}
		});
	}
	
	public static void roleinfo(String params) {
		LogManager.d("创建角色：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverId = json.optString("serverNo");
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			String roleId = json.optString("roleId");
			String roleLevel = json.optString("level");
			String time = json.optString("time");
			
			AnalyticsInfo info = new AnalyticsInfo();
			info.setGameUserID(roleId);
			info.setGameUserName(roleName);
			info.setRoleLevel(roleLevel);
			info.setRoleVipLevel("0");
			info.setZoneID(serverId);
			info.setZoneName(serverName);
			info.setRegistTimestamp(time);
			RSDKPlatform.getInstance().registAnalytics(info);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void enterGame(String params){
		LogManager.d("进入游戏：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverId = json.optString("serverNo");
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			String roleId = json.optString("roleId");
			String roleLevel = json.optString("level");
			String time = json.optString("time");
			
			AnalyticsInfo info = new AnalyticsInfo();
			info.setGameUserID(roleId);
			info.setGameUserName(roleName);
			info.setRoleLevel(roleLevel);
			info.setRoleVipLevel("0");
			info.setZoneID(serverId);
			info.setZoneName(serverName);
			info.setRegistTimestamp(time);
			RSDKPlatform.getInstance().loginAnalytics(info);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void playerUpLevel(String params){
		LogManager.d("角色升级：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverId = json.optString("serverNo");
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			String roleId = json.optString("roleId");
			String roleLevel = json.optString("level");
			String time = json.optString("time");
			
			AnalyticsInfo info = new AnalyticsInfo();
			info.setGameUserID(roleId);
			info.setGameUserName(roleName);
			info.setRoleLevel(roleLevel);
			info.setRoleVipLevel("0");
			info.setZoneID(serverId);
			info.setZoneName(serverName);
			info.setRegistTimestamp(time);
			RSDKPlatform.getInstance().updateAnalytics(info);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void custom(String params) {
		LogManager.d("新手引导：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverId = json.optString("serverId");
			String roleId = json.optString("roleId");
			String guideId = json.optString("guideId");
			
			AnalyticsInfo info = new AnalyticsInfo();
			info.setGameUserID(roleId);
			info.setZoneID(serverId);
			info.setStep(guideId);
			RSDKPlatform.getInstance().tutorialStepAnalytics(info);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public static void pay(String params) {
		LogManager.d("支付订单：", params);
		try {
			JSONObject json = new JSONObject(params);
			mOrderId = json.optString("myOrderId");   						//游戏订单号
			String productId = json.optString("productId"); 				//商品id（此值需要做成服务端配表）
			String productName = json.optString("productName");  			//商品名称
			mPrice = String.valueOf(json.optInt("productRealPrice") / 100); //实际价格
			
			JSONObject jsonObject = json.getJSONObject("exs");
			mVipLevel = jsonObject.optString("UserGamerVip"); 				//VIP等级
			mRoleLevel = jsonObject.optString("UserLevel"); 				//角色等级
			mRoleName = jsonObject.optString("UserRoleName"); 				//角色名称
			mRoleId = jsonObject.optString("UserRoleId"); 					//角色id
			mServerId = jsonObject.optString("UserServerId"); 				//服务器id
			mServerName = jsonObject.optString("UserServerName"); 			//服务器名字
			mCoinNum = jsonObject.optString("GameMoneyAmount"); 			//充值游戏币金额
			
			ProductInfo info = new ProductInfo();
			info.setPrice(mPrice);
			info.setProductId(productId);
			info.setProductName(productName);
			info.setCoinNum(mCoinNum);
			info.setProductCount("1");
			info.setProductType("元宝");
			info.setZoneId(mServerId);
			info.setGameUserId(mRoleId);
			info.setRoleUserName(mRoleName);
			info.setRoleLevel(mRoleLevel);
			info.setRoleVipLevel(mVipLevel);
			info.setCurrency("CNY");
			info.setPrivateData(mOrderId);
			
			RSDKPlatform.getInstance().pay(info, new PayListener() {
				@Override
				public void onPaySuccess(String msg) {
					LogManager.d("支付成功：", msg);
					AnalyticsInfo info = new AnalyticsInfo();
					info.setGameUserID(mRoleId);
					info.setGameUserName(mRoleName);
					info.setRoleLevel(mRoleLevel);
					info.setRoleVipLevel(mVipLevel);
					info.setZoneID(mServerId);
					info.setZoneName(mServerName);
					info.setOrderID(mOrderId);
					info.setPrice(mPrice);
					info.setCoinNum(mCoinNum);
					info.setProductCount("1");
					info.setProductType("元宝");
					info.setCurrency("CNY");
					RSDKPlatform.getInstance().payAnalytics(info);
				}
				@Override
				public void onPayFail(String msg) {
					LogManager.d("支付失败：", msg);
				}
				@Override
				public void onPayCancel(String msg) {
					LogManager.d("支付取消：", msg);
				}
			});
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
}