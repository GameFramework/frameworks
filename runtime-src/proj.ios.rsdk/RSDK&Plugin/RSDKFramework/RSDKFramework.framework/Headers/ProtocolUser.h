/** @file ProtocolUser.h
 */
#ifndef __CCX_PROTOCOL_USER_H__
#define __CCX_PROTOCOL_USER_H__

#include "PluginProtocol.h"
#include <map>
#include <string>

namespace rsdk { namespace framework {
/// \typedef std::map<std::string, std::string> TUserDeveloperInfo
/// typedef TUserDeveloperInfo.
typedef std::map<std::string, std::string> TUserDeveloperInfo;
/** @brief Plugin_type enum, with inline docs */
typedef enum
{
	kInitSuccess = 0,/**< enum value is callback of succeeding in initing sdk. */
	kInitFail=1,/**< enum  value is callback of failing to init sdk. */
    kLoginSuccess=2,/**< enum value is callback of succeeding in login.*/
    kLoginNetworkError=3,/**< enum value is callback of network error*/
    kLoginNoNeed=4,/**< enum value is callback of no need login.*/
    kLoginFail=5,/**< enum value is callback of failing to login. */
    kLoginCancel=6,/**< enum value is callback of canceling to login. */
    kLogoutSuccess=7,/**< enum value is callback of succeeding in logout. */
    kLogoutFail=8,/**< enum value is callback of failing to logout. */
    kPlatformEnter=9,/**< enum value is callback after enter platform. */
    kPlatformBack=10,/**< enum value is callback after exit antiAddiction. */
    kPausePage=11,/**< enum value is callback after exit pause page. */
    kExitPage=12,/**< enum value is callback after exit exit page. */
    kAntiAddictionQuery=13,/**< enum value is callback after querying antiAddiction. */
    kRealNameRegister=14,/**< enum value is callback after registering realname. */
    kAccountSwitchSuccess=15,/**< enum alue is callback of succeeding in switching account. */
    kAccountSwitchFail=16,/**< enum value is callback of failing to switch account. */
    kBindUserSuccess=17,
    kBindUserFailed=18,
    kRegisterSuccess=19,
    kRegisterFailed=20,
    kAntiAddictionNoCertification=21,
    kAntiAddictionAdult=22,
    kAntiAddictionNoAdult=23,

} UserActionResultCode;
/** @brief ToolBarPlace enum, with inline docs */
typedef enum
{
    kToolBarTopLeft = 1,/**< enum the toolbar is at topleft. */
    kToolBarTopRight,/**< enum the toolbar is at topright. */
    kToolBarMidLeft,/**< enum the toolbar is at midleft. */
    kToolBarMidRight,/**< enum the toolbar is at midright. */
    kToolBarBottomLeft,/**< enum the toolbar is at bottomleft. */
    kToolBarBottomRight,/**< enum the toolbar is at bottomright. */
} ToolBarPlace;

class ProtocolUser;
/**   
 *@class  UserActionListener
 *@brief the interface of user callback  
 */
class UserActionListener
{
public:
	/**   
	 *@brief 用户插件回调方法
	 *@param 用户协议对象(用户插件)
	 *@param 回调代码
	 *@param 回调的信息
	 */
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg) = 0;
};
/**   
 *  @class  ProtocolUser  
 */
class ProtocolUser : public PluginProtocol
{
public:
    /**
     @brief User login
     */
    void login();
    void loginWithCustomParams(std::string customParams);
    
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
    
    /*
     防沉迷的状态查询
     */
    void antiAddictionQuery();
    
    /**
     获得平台用户ID
     */
    std::string getUserID();
    
    /*
     * 得到facebook登录ID，如果SDK没有facebook登录，则返回空
     */
    std::string getFacebookUserID();
    /*
     * 得到第三方登录的userID，如果SDK没有第三方登录，则返回空（facebook，vk，kakao都是第三方登陆）
     */
    std::string getThirdUserId();
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
    void setActionListener(UserActionListener* userlistener);
    /**
     @brief 获得用户系统回调类
     @return the listener
     */
    UserActionListener* getActionListener();

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
    static std::string getCustomData();
private:
    
};

}} // namespace rsdk { namespace framework {

#endif /* __CCX_PROTOCOL_USER_H__ */
