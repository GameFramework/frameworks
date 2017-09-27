package com.sdk.mgr;

public class SDKDefine {
	/**
	 * 初始化
	 */
	public final static int EVENT_INIT 			= 10000;
	
	/**
	 * 请求登录
	 */
	public final static int EVENT_LOGIN 		= 10001;
	
	/**
	 * 请求注销
	 */
	public final static int EVENT_LOGOUT 		= 10002;
	
	/**
	 * 请求支付
	 */
	public final static int EVENT_PAY 			= 10003;
	
	/**
	 * 创建角色
	 */
	public final static int EVENT_ROLEINFO 		= 10004;
	
	/**
	 * 进入游戏
	 */
	public final static int EVENT_ENTER 		= 10005;
	
	/**
	 * 玩家升级
	 */
	public final static int EVENT_UPLEVEL 		= 10006;
	
	/**
	 * 设置分数
	 */
	public final static int EVENT_SCORE 		= 10007;
	
	/**
	 * 退出游戏
	 */
	public final static int EVENT_EXIT 			= 10008;
	
	/**
	 * 切换账号
	 */
	public final static int EVENT_CHANGE 		= 10009;
	
	/**
	 * 顾客事件
	 */
	public final static int EVENT_CUSTOM 		= 20001;
	
	
	/**
	 * 失败返回码
	 */
	public static final int RESULT_FAIL 		= -1;
	
	/**
	 * 成功返回码
	 */
	public static final int RESULT_SUCCESS 		= 0;
	
	/**
	 * 取消返回码
	 */
	public static final int RESULT_CANCEL 		= 1;
	
	/**
	 * 支付中
	 */
	public static final int RESULT_INAPPBILLING = -2;
	
}
