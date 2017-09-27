package com.sdk.mgr;

import org.json.JSONException;
import org.json.JSONObject;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Message;

public class SDKManager{
	public static Activity mActivity = null;
	public static SDKManager instance = null;
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
		utility.setPlatformId(0);
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
	}
	
	public static void login() {
		LogManager.d("登入:", "login======");
	}

	public static void logout() {
		LogManager.d("登出:", "logout======");
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
			int roleId = json.optInt("roleId");  					//角色ID
			int level = json.optInt("level");  						//等级
			String time = json.optString("time");
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
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
}