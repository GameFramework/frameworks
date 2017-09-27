package com.sdk.mgr;

import java.util.HashMap;
import java.util.Map;

import org.json.JSONException;
import org.json.JSONObject;

import com.talkingsdk.MainApplication;
import com.talkingsdk.SdkBase;
import com.talkingsdk.ZQCode;
import com.talkingsdk.ZqgameSdkListener;
import com.talkingsdk.models.PayData;
import com.talkingsdk.models.PlayerData;

import android.app.Activity;
import android.os.Bundle;
import android.os.Message;


public class SDKManager implements ZqgameSdkListener{
	public static MainApplication mainInstance = null;
	public static SdkBase sdkInstance = null;
	public static Activity mActivity = null;
	public static SDKManager instance = null;
	
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
		mainInstance = MainApplication.getInstance();		
		sdkInstance = mainInstance.getSdkInstance();
		mainInstance.setZqgameSdkListener(this);
		sdkInstance.setCurrentActivity(activity);
		mainInstance.onCreate(savedInstanceState);
		
		String pid = mainInstance.getPropertiesByKey("PlatformId");
		utility.setPlatformId(Integer.parseInt(pid));
	}
	
	/*
	 * 初始化完成回调
	 */
	@Override
	public void onInitComplete(String arg0) {
		LogManager.d("onInitComplete:",arg0);
		try {
			JSONObject json = new JSONObject(arg0);
			int platformId = json.optInt("PlatformId");
			int code = json.optInt("code");
			String msg = json.optString("msg");
			LogManager.d("初始化完成:","platformId=" + platformId + "code=" + code + "msg:" + msg);
			
			if(ZQCode.CODE_INIT_SUCCESS == code){
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_SUCCESS);
				clientJson.put("platId", platformId);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
			}else{
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_FAIL);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_INIT), clientJson.toString(), "");
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 登入成功回调
	 */
	@Override
	public void onLoginResult(String arg0) {
		LogManager.d("onLoginResult:",arg0);
		try {
			JSONObject json = new JSONObject(arg0);
			String ext = json.optString("Ext");
			String status = new JSONObject(ext).getString("status");
			if(String.valueOf(ZQCode.CODE_LOGIN_SUCCESS).equals(status)){
				//登录成功
				String UserId = json.optString("UserId");
				String UserName = json.optString("UserName");
				String NickName = json.optString("NickName");
				String Password = json.optString("Password");
				String SessionId = json.optString("SessionId");
				String pid = sdkInstance.getPlatformId();
				
				LogManager.d("登入成功：", "UserId=" + UserId + "UserName=" + UserName + "NickName=" + NickName + 
						"Password=" + Password + "SessionId=" + SessionId + "pid=" + pid);
				
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_SUCCESS);
				clientJson.put("platId", pid);
				clientJson.put("uid", UserId);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), SessionId);
				
				//显示悬浮窗（登录后调用）
				sdkInstance.showToolBar();
			}else{
				//登录失败
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_FAIL);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGIN), clientJson.toString(), "");
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * 支付完成回调
	 */
	@Override
	public void onPayResult(String arg0) {
		LogManager.d("onPayResult:", arg0);
		try {
			JSONObject json = new JSONObject(arg0);
			String ext = json.optString("Ext");
			String status = new JSONObject(ext).getString("status");
			if(String.valueOf(ZQCode.CODE_PAY_SUCCESS).equals(status)){
			}else{
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void onResult(String arg0){
		LogManager.d("onResult:", arg0);
	}
	
	@Override
	public void onChangeAccountResult(String arg0){
		LogManager.d("onChangeAccountResult:", arg0);
		try {
			JSONObject json = new JSONObject(arg0);
			String ext = json.optString("Ext");
			String status = new JSONObject(ext).getString("status");
			if(String.valueOf(ZQCode.CODE_CHANGEACCOUNT_SUCCESS).equals(status)){
				String UserId = json.optString("UserId");
				String UserName = json.optString("UserName");
				String NickName = json.optString("NickName");
				String Password = json.optString("Password");
				String SessionId = json.optString("SessionId");
				String pid = sdkInstance.getPlatformId();
				
				LogManager.d("切换账号成功：", "UserId=" + UserId + "UserName=" + UserName + "NickName=" + NickName + 
						"Password=" + Password + "SessionId=" + SessionId + "pid=" + pid);
				
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_SUCCESS);
				clientJson.put("platId", pid);
				clientJson.put("uid", UserId);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_CHANGE), clientJson.toString(), SessionId);
			}else{
				JSONObject clientJson = new JSONObject();
				clientJson.put("result", SDKDefine.RESULT_FAIL);
				utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_CHANGE), clientJson.toString(), "");
			}
			
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void onLogoutResult(String arg0){
		LogManager.d("onLogoutResult:", arg0);
		utility.runNativeCallback(String.valueOf(SDKDefine.EVENT_LOGOUT), "",  "");
	}
	
	@Override
	public void onExitAppResult(){
		mActivity.finish();
		System.exit(0);
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
		LogManager.d("初始化：", "init======");
		sdkInstance.initCommonSdkObject(mActivity);
	}
	
	public static void login() {
		LogManager.d("登入：", "login======");
		sdkInstance.login();
	}

	public static void logout() {
		LogManager.d("登出：", "logout======");
		sdkInstance.destroyToolBar();   	//隐藏悬浮窗（登出前调用）
		sdkInstance.logout();
	}
	
	public static void exit() {
		LogManager.d("退出：", "exit======");
		sdkInstance.onKeyBack();
	}
	
	public static void roleinfo(String params) {
		LogManager.d("创建角色：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverNo = json.optString("serverNo");       	//区服
			String serverName = json.optString("serverName");   	//服务器名称
			String roleName = json.optString("roleName"); 			//角色名称
			int roleId = json.optInt("roleId");  					//角色ID
			int level = json.optInt("level");  						//等级
			String time = json.optString("time");
			
			Map<String,String> exs = new HashMap<String,String>();
			exs.put("roleCTime",time);
			
			PlayerData _playerData = new PlayerData();
			_playerData.setServerNo(serverNo);
			_playerData.setServerName(serverName);
			_playerData.setRoleName(roleName);
			_playerData.setRoleId(roleId);
			_playerData.setLevel(level);
			_playerData.setEx(exs);
			sdkInstance.createRole(_playerData);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void enterGame(String params){
		LogManager.d("进入游戏：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverNo = json.optString("serverNo");
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			int roleId = json.optInt("roleId");
			int level = json.optInt("level");
			String time = json.optString("time");
			
			Map<String,String> exs = new HashMap<String,String>();
			exs.put("roleCTime",time);
			
			PlayerData _playerData = new PlayerData();
			_playerData.setServerNo(serverNo);
			_playerData.setServerName(serverName);
			_playerData.setRoleName(roleName);
			_playerData.setRoleId(roleId);
			_playerData.setLevel(level);
			_playerData.setEx(exs);
			sdkInstance.enterGame(_playerData);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void playerUpLevel(String params){
		LogManager.d("角色升级：", params);
		try {
			JSONObject json = new JSONObject(params);
			String serverNo = json.optString("serverNo");
			String serverName = json.optString("serverName");
			String roleName = json.optString("roleName");
			int roleId = json.optInt("roleId");
			int level = json.optInt("level");
			String time = json.optString("time");
			
			Map<String,String> exs = new HashMap<String,String>();
			exs.put("roleCTime",time);
			
			PlayerData _playerData = new PlayerData();
			_playerData.setServerNo(serverNo);
			_playerData.setServerName(serverName);
			_playerData.setRoleName(roleName);
			_playerData.setRoleId(roleId);
			_playerData.setLevel(level);
			_playerData.setEx(exs);
			sdkInstance.userUpLevel(_playerData);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	public static void setScore(String params){
		LogManager.d("设置分数：", params);
		try {
			JSONObject json = new JSONObject(params);
			String sorce = json.optString("sorce");
			String rank = json.optString("rank");
			sdkInstance.uploadScore(sorce,rank);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public static void pay(String params) {
		LogManager.d("支付订单：", params);
		try {
			JSONObject json = new JSONObject(params);
			String myOrderId = json.optString("myOrderId");   				//游戏订单号
			String productId = json.optString("productId"); 				//商品id（此值需要做成服务端配表）
			String productName = json.optString("productName");  			//商品名称
			int productRealPrice = json.optInt("productRealPrice"); 		//实际价格
			int productIdealPrice = json.optInt("productIdealPrice"); 		//理想价格
			int productCount = json.optInt("productCount"); 				//商品数量
			String description = json.optString("description");  			//商品描述
			String submitTime = json.optString("submitTime"); 				//创建订单返回的时间
			
			JSONObject jsonObject = json.getJSONObject("exs");
			String UserBalance = jsonObject.optString("UserBalance");  		//用户余额
			String UserGamerVip = jsonObject.optString("UserGamerVip"); 	//VIP等级
			String UserLevel = jsonObject.optString("UserLevel"); 			//角色等级
			String UserPartyName = jsonObject.optString("UserPartyName"); 	//工会
			String UserRoleName = jsonObject.optString("UserRoleName"); 	//角色名称
			String UserRoleId = jsonObject.optString("UserRoleId"); 		//角色id
			String UserServerName = jsonObject.optString("UserServerName"); //服务器名称
			String UserServerId = jsonObject.optString("UserServerId"); 	//服务器id
			int GameMoneyAmount = jsonObject.optInt("GameMoneyAmount"); 	//充值游戏币金额，不包含赠送金额 请按(支付金额*人民币与游戏币兑换率，比如，6元60钻石，此处传60，应用宝渠道通过此值确定商品价格及游戏币数量)
			String GameMoneyName = jsonObject.optString("GameMoneyName"); 	//货币名称，如元宝、钻石
			String UserId = jsonObject.optString("UserId"); 				//用户id（accid）
			String LoginAccount = jsonObject.optString("LoginAccount"); 	//登陆帐户(account)
			String LoginDataEx = jsonObject.optString("LoginDataEx"); 		//登陆扩展信息(ext)
			String LoginSession = jsonObject.optString("LoginSession"); 	//登陆session(session)
			String AccessKey = jsonObject.optString("AccessKey"); 			//sdk服务端返回的sign，某些渠道需要签名验证
			String OutOrderID = jsonObject.optString("OutOrderID"); 		//第三方订单号(平台订单号plat_order)
			String NoticeUrl = jsonObject.optString("NoticeUrl"); 			//支付回调地址
			
			PayData payData = new PayData();
			payData.setSubmitTime(submitTime+"");
			payData.setMyOrderId(myOrderId);
			payData.setDescription(description);
			payData.setProductCount(productCount);
			payData.setProductId(productId+"");
			payData.setProductIdealPrice(productIdealPrice);
			payData.setProductRealPrice(productRealPrice);
			payData.setProductName(productName);
			Map<String,String> exs = new HashMap<String,String>();
			exs.put("UserBalance", UserBalance);
			exs.put("UserGamerVip", UserGamerVip);
			exs.put("UserLevel", UserLevel);
			exs.put("UserPartyName", UserPartyName);
			exs.put("UserRoleName", UserRoleName);
			exs.put("UserRoleId", UserRoleId);
			exs.put("UserServerName", UserServerName);
			exs.put("UserServerId", UserServerId);
			exs.put("GameMoneyAmount", GameMoneyAmount+"");
			exs.put("GameMoneyName", GameMoneyName);
			exs.put("UserId", UserId);
			exs.put("LoginAccount", LoginAccount);
			exs.put("LoginDataEx", LoginDataEx);
			exs.put("LoginSession", LoginSession);
			exs.put("AccessKey", AccessKey);
			exs.put("OutOrderID", OutOrderID);
			exs.put("NoticeUrl",NoticeUrl);
			payData.setEx(exs);

			sdkInstance.pay(payData);
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
}