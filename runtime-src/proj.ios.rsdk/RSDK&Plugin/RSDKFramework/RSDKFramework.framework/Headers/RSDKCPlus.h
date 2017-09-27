//
//  RSDKCPlus.h
//  RSDKFramework
//
//  Created by 曹恩康 on 2017/4/20.
//  Copyright © 2017年 rayjoy. All rights reserved.
//

#ifndef RSDKCPlus_h
#define RSDKCPlus_h

#include "AgentManager.h"
#include "PluginChannel.h"
#include "string.h"

using namespace rsdk::framework;
using namespace std;

namespace rsdk { namespace framework {
    
    // '统计类型'枚举
    enum RSDKCPlusAnalyticsFlag {
        /**
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
        RSDKCPlus_Analytics_SetGameUserInfo=1,
        RSDKCPlus_Analytics_PayRequest=2,
        RSDKCPlus_Analytics_PaySuccess=3,
        RSDKCPlus_Analytics_SendVirtualCurrency=4,
        RSDKCPlus_Analytics_PaymentFinish=5,
        RSDKCPlus_Analytics_ExpendProps=6,
        RSDKCPlus_Analytics_ReceiveTask=7,
        RSDKCPlus_Analytics_FinishTask=8,
        RSDKCPlus_Analytics_FailTask=9,
        RSDKCPlus_Analytics_SetAge=10,
        RSDKCPlus_Analytics_SetGender=11,
        RSDKCPlus_Analytics_UserLeverUp=12,
        RSDKCPlus_Analytics_Install=13,
        RSDKCPlus_Analytics_NewbieGuideEnd=14,
        RSDKCPlus_Analytics_GuestLoginSuccess=15,
        RSDKCPlus_Analytics_ShowToolbar=16,
        RSDKCPlus_Analytics_BITutorial = 98,
        RSDKCPlus_Analytics_BIHeartBeat = 99,
    };
    
    /**
     初始化系统的回调函数
     
     @ InitResultCode {
     
       kInitSuccess, 0-初始化成功
       kInitFailed   1-初始化失败
     
     }
     */
    typedef void (InitCallBack)(InitResultCode code, const char *msg);
    
    /**
     用户系统回调函数
     
     @ UserActionResultCode {
     
       kInitSuccess = 0,       0-sdk初始化成功
       kInitFail,              1-sdk初始化失败
       kLoginSuccess,          2-登录成功
       kLoginNetworkError,     3-网络连接失败
       kLoginNoNeed,           4-无需登录
       kLoginFail,             5-登录失败
       kLoginCancel,           6-用户取消了登录
       kLogoutSuccess,         7-注销登录成功
       kLogoutFail,            8-注销登录失败
       kPlatformEnter,         9-进入用户平台中心
       kPlatformBack,         10-退出用户平台中心
       kPausePage,            11-暂停游戏
       kExitPage,             12-退出游戏
       kAntiAddictionQuery,   13-防沉迷注册
       kRealNameRegister,     14-实名注册
       kAccountSwitchSuccess, 15-切换用户成功
       kAccountSwitchFail,    16-切换用户失败
       kBindUserSuccess,      17-绑定账号成功
       kBindUserFailed        18-绑定账号失败
     
     }
     */
    typedef void (UserCallBack)(ProtocolUser *pPlugin, UserActionResultCode code, const char *msg);
    
    /**
     支付系统回调函数
     
     @ PayResultCode {
     
       kPaySuccess = 0,               0-支付成功
       kPayFail,                      1-支付失败
       kPayCancel,                    2-用户取消了支付
       kPayNetworkError,              3-网络错误
       kPayProductionInforIncomplete, 4-商品信息参数不完整
       kPayInitSuccess,               5-支付SDK初始化成功
       kPayInitFail,                  6-支付SDK初始化失败
       kPayNowPaying,                 7-支付操作正在进行中
       kPayRechareSuccess,            8-重新支付成功
     
     }
     */
    typedef void (PaymentCallBack)(PayResultCode ret, const char *msg, TProductInfo info);
    
    /**
     分享系统的回调函数
     */
    typedef void (ShareCallBack)(ShareResultCode ret, const char *msg);
    
    /**
     社交系统的回调函数
     */
    typedef void (SocialCallBack)(SocialRetCode ret, const char *msg);
    
    /**
     推送系统的回调函数
     */
    typedef void (PushCallBack)(PushActionResultCode ret, const char *msg);
    
    class RSDKCPlus {
        
    public:
        #pragma mark - RSDCPlus instance
        // RSDCPlus instance
        static RSDKCPlus *getInstance();
        
        #pragma mark -
        // 清除对象
        static void purge();
        // 卸载插件
        void unloadPlugins();
        
        #pragma mark - 初始化
        /**
         【【【'init'初始化】】】
         */
        void init(std::string appKey, std::string appSecret, std::string privateKey, bool debug, InitCallBack *initCallBack);
        
        #pragma mark - 登陆
        /**
         【【【'login'登陆】】】
         */
        // login mode 1
        void login(std::string customParams, UserCallBack *userCallBack);
        // login mode 2
        void login(std::string customParams, std::string pluginId, UserCallBack *userCallBack);
        
        #pragma mark - 登出
        /**
         【【【'logout'登出】】】
         */
        void logout();
        
        #pragma mark - 切换账号
        /**
         【【【'accountSwitch'切换账号】】】
         */
        void accountSwitch();
        
        #pragma mark - 平台中心
        /**
         【【【'enterPlatform'平台中心】】】
         */
        void enterPlatform();
        
        #pragma mark - 绑定账号
        /**
         【【【'bindAccount'绑定账号】】】
         */
        void bindAccount();
        
        #pragma mark - 显示悬浮窗
        /**
         【【【'showToolBar'显示悬浮窗】】】
         */
        // showToolBar mode 1
        void showToolBar();
        // showToolBar mode 2
        void showToolBar(int code);
        
        #pragma mark - 隐藏悬浮窗
        /**
         【【【'hideToolBar'隐藏悬浮窗】】】
         */
        void hideToolBar();
        
        #pragma mark - 防沉迷的状态查询
        // 防沉迷的状态查询
        void antiAddictionQuery();
        
        #pragma mark - 支付
        /**
         【【【'pay'支付】】】
         */
        // pay mode 1
        void pay(std::map<std::string, std::string> productInfo, PaymentCallBack *paymentCallBack);
        // pay mode 2
        void pay(std::map<std::string, std::string> productInfo, std::string pluginId, PaymentCallBack *paymentCallBack);
        
        #pragma mark - 分享
        /**
         【【【'share'分享】】】
         */
        // share mode 1
        void share(std::map<std::string, std::string> shareInfo, ShareCallBack *shareCallBack);
        // share mode 2
        void share(std::map<std::string, std::string> shareInfo, std::string pluginId, ShareCallBack *shareCallBack);
        
        #pragma mark - 邀请
        /**
         【【【'invite'邀请】】】
         */
        void invite(std::map<std::string, std::string> inviteInfo);
        
        #pragma mark - 统计
        /**
         【【【'trackEvent'统计】】】
         */
        void trackEvent(RSDKCPlusAnalyticsFlag eventCode, std::map<std::string, std::string> eventInfo);
        
        #pragma mark - 获取子平台ID
        // 获取子平台ID
        std::string getSubAppId();
        
        #pragma mark - 获取社交好友信息
        // 获取社交好友信息
        void getFriends();
        
        #pragma mark - 获取自己信息方法
        // 获取自己信息方法
        void getMyInfo();
        
        #pragma mark - 设置回调监听
        // 设置回调监听
        void setRSDKCPlusInitCallBackListener(InitCallBack *_initCallBack);
        void setRSDKCPlusUserCallBackListener(UserCallBack *_userCallBack);
        void setRSDKCPlusPaymentCallBackListener(PaymentCallBack *_paymentCallBack);
        void setRSDKCPlusShareCallBackListener(ShareCallBack *_shareCallBack);
        void setRSDKCPlusSocialCallBackListener(SocialCallBack *_socialCallBack);
        void setRSDKCPlusPushCallBackListener(PushCallBack *_pushCallBack);
        
    private:
        #pragma mark -
        // 声明'PluginChannel'对象
        PluginChannel *rsdkChannel;
        // 声明'RSDKCPlus'对象
        static RSDKCPlus *_rsdkCPlusInstance;
        
        // map 对象集合
        std::map<std::string, ProtocolUser            *> *_pluginsUserMap;
        std::map<std::string, ProtocolIAP             *> *_pluginsIAPMap;
        std::map<std::string, ProtocolShare           *> *_pluginsShareMap;
        std::map<std::string, ProtocolSocial          *> *_pluginsSocialMap;
        std::map<std::string, ProtocolAnalytics       *> *_pluginsAnalyticsMap;
        std::map<std::string, ProtocolCustomerService *> *_pluginsCustomerServiceMap;
        // 回调函数
        InitCallBack    *_initCallBack;    // init
        UserCallBack    *_usrCallBack;     // 用户
        PaymentCallBack *_paymentCallBack; // 支付
        ShareCallBack   *_shareCallBack;   // 分享
        SocialCallBack  *_socialCallBack;  // 社交
        PushCallBack    *_pushCallBack;    // 推送
        // new
        RSDKCPlus();
        // 析构函数
        virtual ~RSDKCPlus();
        // 判断字符串是否为纯数字
        bool isDigit(std::string str);
    };
}}

#endif /* RSDKCPlus_h */
