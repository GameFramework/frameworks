//
//  PluginChannel.h
//  libRSDKPluginIOS
//
//  Created by tonetchen on 15-2-2.
//

#ifndef __MY_PURCHASE_H__
#define __MY_PURCHASE_H__

#include "AgentManager.h"
#include "string.h"

using namespace rsdk::framework;
using namespace std;

namespace rsdk { namespace framework {
/**用户系统回调函数**/
    
//    UserActionResultCode
//    kInitSuccess = 0, sdk初始化成功
//    kInitFail, 1-sdk初始化失败
//    kLoginSuccess, 2-登录成功
//    kLoginNetworkError, 3-网络连接失败
//    kLoginNoNeed, 4-无需登录
//    kLoginFail, 5-登录失败
//    kLoginCancel, 6-用户取消了登录
//    kLogoutSuccess, 7-注销登录成功
//    kLogoutFail, 8-注销登录失败
//    kPlatformEnter, 9-进入用户平台中心
//    kPlatformBack, 10-退出用户平台中心
//    kPausePage, 11-暂停游戏
//    kExitPage, 12-退出游戏
//    kAntiAddictionQuery, 13-防沉迷注册
//    kRealNameRegister, 14-实名注册
//    kAccountSwitchSuccess, 15-切换用户成功
//    kAccountSwitchFail, 16-切换用户失败
//    kBindUserSuccess,    17-绑定账号成功
//    kBindUserFailed     18-绑定账号失败
typedef void(UserCallBack)(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);
    
/**支付系统回调函数**/
    
//    kPaySuccess = 0, 支付成功
//    kPayFail, 1-支付失败
//    kPayCancel, 2-用户取消了支付
//    kPayNetworkError, 3-网络错误
//    kPayProductionInforIncomplete, 4-商品信息参数不完整
//    kPayInitSuccess, 5-支付SDK初始化成功
//    kPayInitFail, 6-支付SDK初始化失败
//    kPayNowPaying, 7-支付操作正在进行中
//    kPayRechareSuccess, 8-重新支付成功
typedef void(PaymentCallBack)(PayResultCode ret, const char* msg, TProductInfo info);
    
typedef void(ShareCallBack)(ShareResultCode ret,const char* msg);
    
typedef void(SocialCallBack)(SocialRetCode ret,const char* msg);
    
typedef void(PushCallBack)(PushActionResultCode ret,const char* msg);
    
//    kInitSuccess,    0-初始化成功
//    kInitFailed      1-初始化失败
typedef void(InitCallBack)(InitResultCode code, const char* msg);
    
class PluginChannel:public UserActionListener,public PayResultListener,public ShareResultListener,public SocialListener,public InitActionListener
{
public:
    static PluginChannel* getInstance();
    static void purge();
    
    /*
     @brief debug模式 在调用loadPlugins之前调用该方法
     */
    void setDebugMode(bool debugflag = false);
    
    /*
     @brief 载入插件，同时进行插件的初始化
     */
    void loadPlugins(string appKey,string appSecret,string privateKey,string oauthLoginServer);
    
   	//卸载插件
   	void unloadPlugins();
    
    /*
     获得统计ID
     */
    std::string getSubAppId();
    
    /*
     获得游戏包的build
     */
    std::string getPackageBuild();
    
    /*
     获得游戏包的version
     */
    std::string getPackageVersion();
    
    //设置用户系统回调监听对象
    void setChannelUserCallback(UserCallBack *_uCallBack);
    
    //设置支付系统回调监听对象
    void setChannelPayCallback(PaymentCallBack *_pCallBack);
    
    //分享回调监听对象
    void setChannelShareCallback(ShareCallBack *_sCallBack);
    
    //社交回调监听对象
    void setChannelSocialCallback(SocialCallBack *_scCallBack);
    
    //初始化回调监听对象
    void setChannelInitCallback(InitCallBack *_initCallBack);
    
    /*
     返回用户插件列表
     */
    map<std::string , ProtocolUser*>* getUserMaps();
    /*
     返回用户插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolUser* getUserProtocol(std::string pluginID);
    /*
     调起协议登陆界面
     @param 登陆参数，跟指定登陆方式的参数相同，多加一个透传字段customParams
     */
    void rsdkLogin(std::string pluginID,std::string customParams);
   	/*
     返回支付插件列表
     */
    map<std::string , ProtocolIAP*>* getIAPMaps();
    /*
     返回支付插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolIAP* getIAPProtocol(std::string pluginID);
    /*
     调起协议支付界面
     @param 支付参数，跟指定支付方式的参数相同
     */
    void rsdkPay(std::string pluginID,std::map<std::string, std::string> payInfo);
    /*
     返回分享插件列表
     */
    map<std::string , ProtocolShare*>* getShareMaps();
    /*
     返回分享插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolShare* getShareProtocol(std::string pluginID);
    /*
     调起协议分享界面
     @param 分享参数，跟指定分享方式的参数相同，多加一个透传字段customParams
     */
    void rsdkShare(std::string pluginID,std::map<std::string, std::string> shareInfo,std::string customParams);
    /*
     返回社交插件列表
     */
    map<std::string , ProtocolSocial*>* getSocialMaps();
    /*
     返回社交插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolSocial* getSocialProtocol(std::string pluginID);
    /*
     返回统计插件列表
     */
    map<std::string , ProtocolAnalytics*>* getAnalyticsMaps();
    /*
     返回统计插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolAnalytics* getAnalyticsProtocol(std::string pluginID);
    /*
     返回广告插件列表
     */
    map<std::string , ProtocolAds*>* getAdsMaps();
    /*
     返回广告插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolAds* getAdsProtocol(std::string pluginID);
    //推送
    map<std::string,ProtocolPush*>* getPushMaps();
    /*
     返回推送插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolPush* getPushProtocol(std::string pluginID);
    //客服
    map<std::string,ProtocolCustomerService*>* getCustomerServiceMaps();
    /*
     返回客服插件
     @param 插件ID，如果传入空，则返回列表中的第一个插件
     */
    ProtocolCustomerService* getCustomerServiceProtocol(std::string pluginID);
    
    void doAnalytics(LogEventParamMap analyticsParam);
    
private:
    PluginChannel();
    virtual ~PluginChannel();
    static PluginChannel* _pInstance;
    //user 对象集合
    std::map<std::string , ProtocolUser*>* _pluginsUserMap;
    //iap 对象集合
    std::map<std::string , ProtocolIAP*>* _pluginsIAPMap;
    //share 对象集合
    std::map<std::string , ProtocolShare*>* _pluginsShareMap;
    //social 对象集合
    std::map<std::string , ProtocolSocial*>* _pluginsSocialMap;
    //push 对象集合
    std::map<std::string , ProtocolPush*>* _pluginsPushMap;
    //analytics 对象集合
    std::map<std::string , ProtocolAnalytics*>* _pluginsAnalyticsMap;
    //ad 对象集合
    std::map<std::string , ProtocolAds*>* _pluginsAdsMap;
    //客服 对象集合
    std::map<std::string , ProtocolCustomerService*>* _pluginsCustomerServiceMap;
    
    UserCallBack *_usrCallback;
    PaymentCallBack *_payCallback;
    ShareCallBack *_shareCallback;
    SocialCallBack *_socialCallback;
    InitCallBack *_initCallBack;
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);
    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info);
    virtual void onShareResult(ShareResultCode ret,const char* msg);
    virtual void onSocialResult(SocialRetCode ret,const char* msg);
    virtual void onInitResult(InitResultCode ret,const char* msg);
};
}}
#endif

