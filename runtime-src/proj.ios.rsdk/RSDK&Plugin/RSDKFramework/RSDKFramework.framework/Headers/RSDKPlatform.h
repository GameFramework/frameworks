//
//  RSDK.h
//  RSDKFramework
//
//  Created by 邹明明 on 17/2/16.
//  Copyright © 2017年 . All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Wrapper.h"
#import "PluginChannel.h"

enum kRSDK_Analytics_FLAG{
    /*
     1.统计玩家账户,BI 登录
     2.充值请求
     3.充值成功
     4.发送虚拟币
     5.付费点支付完成
     6.消耗物品
     7.接到任务
     8.完成任务
     9.任务失败
     10.设置年龄
     11.设置性别
     12.角色升级
     13.统计安装
     14.新手引导结束
     15.游客登陆成功
     16.显示弹窗通知
     98.BI 新手引导
     99.BI 在线
     */
    RSDK_Analytics_SetGameUserInfo=1,
    RSDK_Analytics_PayRequest=2,
    RSDK_Analytics_PaySuccess=3,
    RSDK_Analytics_SendVirtualCurrency=4,
    RSDK_Analytics_PaymentFinish=5,
    RSDK_Analytics_ExpendProps=6,
    RSDK_Analytics_ReceiveTask=7,
    RSDK_Analytics_FinishTask=8,
    RSDK_Analytics_FailTask=9,
    RSDK_Analytics_SetAge=10,
    RSDK_Analytics_SetGender=11,
    RSDK_Analytics_UserLeverUp=12,
    RSDK_Analytics_Install=13,
    RSDK_Analytics_NewbieGuideEnd=14,
    RSDK_Analytics_GuestLoginSuccess=15,
    RSDK_Analytics_ShowToolbar=16,
    RSDK_Analytics_BITutorial = 98,
    RSDK_Analytics_BIHeartBeat = 99,
};

enum kRSDK_UserCallBack_Code{
    /*
     0.失败回调code
     1.登陆成功code
     2.登出成功code
     3.绑定账号成功code
     4.切换账号成功code
     5.防沉迷查询成功code
     */
    RSDK_UserCallBackFail = 0,
    RSDK_LoginSuccess = 1,
    RSDK_LogoutSuccess=2,
    RSDK_BindSuccess=3,
    RSDK_AccountSwitchSuccess=4,
    RSDK_AntiAddictionQuerySuccess=5,
};

enum kRSDK_PayCallBack_Code{
    /*
     0.失败回调code
     1.支付成功code
     */
    RSDK_PayFail = 0,
    RSDK_PaySuccess=1,
};

enum kRSDK_ShareCallBack_Code{
    /*
     0.失败回调code
     1.分享成功code
     */
    RSDK_ShareFail = 0,
    RSDK_ShareSuccess=1,
};

enum kRSDK_SocialCallBack_Code{
    /*
     0.失败回调code
     1.支付成功code
     */
    RSDK_SocialFail = 0,
    RSDK_InviteSuccess=1,
    RSDK_GetMyInfoSuccess=2,
    RSDK_GetFriendsSuccess=3,
};

@protocol RSDKDelegate

@required
/**
 * @Description
 *     用户相关回调方法
 * @params
 *     loginInfo       ----------用户信息
 *     code       ----------回调结果
 **/
-(void)userCallBack:(NSMutableDictionary*)userInfo withCode:(kRSDK_UserCallBack_Code)code;

/**
 * @Description
 *  支付回调方法
 * @params
 *  productInfo   ----------支付信息
 *     code       ----------回调结果
 **/
-(void)payCallBack:(NSMutableDictionary*)productInfo withCode:(kRSDK_PayCallBack_Code)code;

@optional

/**
 * @Description
 *  分享回调方法
 * @params
 *  shareInfo   ----------分享信息
 *     code       ----------回调结果
 **/
-(void)shareCallBack:(NSMutableDictionary*)shareInfo withCode:(kRSDK_ShareCallBack_Code)code;


/**
 * @Description
 *  社交回调方法
 * @params
 *  socialInfo   ----------社交结果信息
 *     code       ----------回调结果
 **/
-(void)socialCallBack:(NSString*)socialInfo withCode:(kRSDK_SocialCallBack_Code)code;

@end

@interface RSDKPlatform : NSObject

+(RSDKPlatform*)sharedRsdk;

/**
 * @Description
 *  初始化方法
 * @params
 *  appKey       ----------appkey
 *  appSecret    ----------appSecret
 *  privateKey   ----------privateKey
 *  delegate    ----------设置代理
 *  debug       ----------是否Debug模式
 **/
-(void)initWithAppKey:(NSString*)appKey appSecret:(NSString*)appSecret privateKey:(NSString*)privateKey setDelegate:(id<RSDKDelegate>)delegate Debug:(BOOL)debug;

/**
 * @Description
 *  获取子平台id方法，返回子平台id
 **/
-(NSString*)getSubAppId;

/**
 * @Description
 *  登陆方法，登陆时调用
 **/
-(void)loginWithCustomParams:(NSString*)customParams;

/**
 * @Description
 *  登陆方法，登陆时调用，游戏有自己的多登陆界面时使用这个方法
 * @params
 *  pluginId       ----------登陆的pluginId
 **/
-(void)loginWithCustomParams:(NSString*)customParams withPluginId:(NSString*)pluginId;

/**
 * @Description
 *  登出方法，登出或者切换账号时调用
 **/
-(void)logout;

/**
 * @Description
 *  切换账号方法，切换账号时调用
 **/
-(void)accountSwitch;

/**
 * @Description
 *  进入平台中心方法，进入平台中心时调用
 **/
-(void)enterPlatform;

/**
 * @Description
 *  绑定账号方法，绑定账号时调用
 **/
-(void)bindAccount;

/**
 * @Description
 *  显示悬浮窗方法，显示悬浮窗时调用
 **/
-(void)showToolBar;

/**
 * @Description
 *  显示悬浮窗方法，显示悬浮窗时调用
 * @params
 *  code    ----------悬浮窗位置
 **/
-(void)showToolBar:(int)code;

/**
 * @Description
 *  隐藏悬浮窗方法，隐藏悬浮窗时调用
 **/
-(void)hideToolBar;

/**
 * @Description
 *  支付方法，点击支付时调用
 * @params
 *  paymentInfo    ----------支付商品信息
 **/
-(void)payWithProduct:(NSMutableDictionary*)productInfo;

/**
 * @Description
 *  支付方法，点击支付时调用，游戏有自己的多支付界面时使用这个方法
 * @params
 *  paymentInfo    ----------支付商品信息
 *  pluginId       ----------支付的pluginId
 **/
- (void)payWithProduct:(NSMutableDictionary*)productInfo withPluginId:(NSString*)pluginId;

/**
 * @Description
 *  分享方法，发分享时调用
 * @params
 *  shareInfo    ----------分享参数信息
 **/
-(void)share:(NSMutableDictionary*)shareInfo;

/**
 * @Description
 *  分享方法，发分享时调用，游戏有自己的多分享界面时使用这个方法
 * @params
 *  shareInfo    ----------分享参数信息
 *  pluginId       ----------分享的pluginId
 **/
-(void)share:(NSMutableDictionary*)shareInfo withPluginId:(NSString*)pluginId;

/**
 * @Description
 *  邀请方法，发邀请时调用
 * @params
 *  inviteInfo    ----------邀请参数信息
 **/
-(void)invite:(NSMutableDictionary*)inviteInfo;

/**
 * @Description
 *  获得社交好友信息方法
 **/
-(void)getFriends;

/**
 * @Description
 *  获取自己信息方法
 **/
-(void)getMyInfo;

/**
 * @Description
 *  统计方法，发统计时调用
 * @params
 *  eventCode    ----------统计code，用于区分不同的统计
 *  eventInfo    ----------统计参数信息
 **/
-(void)trackEvent:(kRSDK_Analytics_FLAG)eventCode eventInfo:(NSMutableDictionary*)eventInfo;

/**
 * @Description
 *  防沉迷的状态查询
 **/
-(void)antiAddictionQuery;

@end
