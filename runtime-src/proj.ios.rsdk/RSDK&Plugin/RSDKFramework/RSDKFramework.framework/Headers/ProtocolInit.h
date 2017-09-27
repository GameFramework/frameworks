//
//  ProtocolInit.h
//  RSDKFramework
//
//  Created by 邹明明 on 16/8/15.
//

#ifndef ProtocolInit_h
#define ProtocolInit_h

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace rsdk { namespace framework {
    /// \typedef std::map<std::string, std::string> TUserDeveloperInfo
    /// typedef TUserDeveloperInfo.
    typedef std::map<std::string, std::string> TInitDeveloperInfo;
    /** @brief Plugin_type enum, with inline docs */
    
    typedef enum
    {
        WInitSuccess=0,    //0-初始化成功
        WInitFailed      //1-初始化失败
    } InitResultCode;

    class ProtocolInit;
    /**
      *@class  UserActionListener
     *@brief the interface of user callback
     */
    class InitActionListener
    {
    public:
        /**
         *@brief 用户插件回调方法
         *@param 用户协议对象(用户插件)
         *@param 回调代码
         *@param 回调的信息
         */
        virtual void onInitResult(InitResultCode code, const char* msg) = 0;
    };
    /**
      *  @class  ProtocolUser
     */
    class ProtocolInit : public PluginProtocol
    {
    public:
        /**
         @brief User login
         */
        void login();
        
        void login(std::string server_id);
        
        /**
         @brief User login
         if the process of logining need to know  the param of server_id ,
         you can use the function
         and if you must change oauthloginserver, you can add the param of oauthLoginServer
         @param server_id
         @param oauthLoginServer
         */
        void login(std::string server_id, std::string oauthLoginServer);
        /**
         @brief Check whether the user logined or not
         @return If user logined, return value is true;
         else return value is false.
         */
        bool isLogined();
        /**
         User Logout
         */
        void logout();
        /*
         show platform center
         */
        void enterPlatform();
        /*
         switch user account
         */
        void accountSwitch();
        
        /*
         show sdk toolbar
         */
        void showToolBar();
        
        /*
         show sdk toolbar with position
         */
        void showToolBar(int position);
        
        /*
         hide sdk toolbar
         */
        void hideToolBar();
        
        /*
         绑定账号
         */
        void bindAccount();
        
        /**
         获得平台用户ID
         */
        std::string getUserID();
        
        /*
         * 得到facebook登录ID，如果SDK没有facebook登录，则返回空
         */
        std::string getFacebookUserID();
        /*
         获得带前缀的平台用户ID
         */
        std::string getUserIDWithPrefix();
        /*
         获得平台用户的前缀，用于区分不同平台
         */
        std::string getUserIDPrefix();
        /*
         获取当前登录类型
         试玩账号  LOGIN_USER_TYPE_TRAIL = 0
         SDK账号系统   LOGIN_USER_TYPE_SDK =1
         facebook  LOGIN_USER_TYPE_FACEBOOK=2
         其他sns平台(非facebook) LOGIN_USER_TYPE_SNS_PLATFORM=3
         游戏平台用户账号   LOGIN_USER_TYPE_GAME_PLATFORM=4
         */
        std::string getLoginUserType();
        
        /**
         @brief 设置用户系统回调类，该类必须继承自UserActionListener
         @param pListener The callback object for user result
         */
        void setInitListener(InitActionListener* initlistener);
        /**
         @brief 获得用户系统回调类
         @return the listener
         */
        //InitActionListener* getInitListener();
        InitActionListener* getInitListener();
        /**
         @brief Check function the plugin support or not
         @param the name of plugin
         @return if the function support ,return true
     	 	 else retur false
         */
        //bool isFunctionSupported(std::string functionName);
        /**
         @brief get plugin id
         @return the plugin id
         */
        std::string getPluginId();
        static std::string getLoginServerId();
        static std::string getLoginServerIp();
    private:
        
    };
    
}} // namespace rsdk { namespace framework {


#endif /* ProtocolInit_h */
