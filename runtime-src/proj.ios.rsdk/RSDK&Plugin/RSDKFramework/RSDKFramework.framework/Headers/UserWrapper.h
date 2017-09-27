//
//  UserWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-9-4.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InterfaceUser.h"
#import "LoginCallbackDataInfo.h"

typedef enum : NSUInteger {
    ACTION_RET_INIT_SUCCESS = 0,
    ACTION_RET_INIT_FAIL=1,
    ACTION_RET_LOGIN_SUCCESS=2,
    ACTION_RET_LOGIN_TIMEOUT=3,
    ACTION_RET_LOGIN_NO_NEED=4,
    ACTION_RET_LOGIN_FAIL=5,
    ACTION_RET_LOGIN_CANCEL=6,
    ACTION_RET_LOGOUT_SUCCESS=7,
    ACTION_RET_LOGOUT_FAIL=8,
    ACTION_RET_PLATFORM_ENTER=9,
    ACTION_RET_PLATFORM_BACK=10,
    ACTION_RET_PAUSE_PAGE=11,
    ACTION_RET_EXIT_PAGE=12,
    ACTION_RET_ANTIADDICTIONQUERY=13,
    ACTION_RET_REALNAMEREGISTER=14,
    ACTION_RET_ACCOUNTSWITCH_SUCCESS=15,
    ACTION_RET_ACCOUNTSWITCH_FAIL=16,
    ACTION_RET_BINDUSER_SUCCESS=17,
    ACTION_RET_BINDUSER_FAILED=18,
    ACTION_RET_REGISTER_SUCCESS=19,
    ACTION_RET_REGISTER_FAILED=20,
    ACTION_RET_ANTI_ADDICTION_NO_CERTIFICATION=21,//查询防沉迷状态-未实名认证
    ACTION_RET_ANTI_ADDICTION_ADULT=22,//查询防沉迷状态-已实名认证-已成年
    ACTION_RET_ANTI_ADDICTION_NO_ADULT=23,//查询防沉迷状态-已实名认证-未成年
} ACTION_RET;

/*
 *  账号类型
 */
typedef enum : NSUInteger {
    //试玩账号
    LOGIN_USER_TYPE_TRAIL = 0,
    /*
     * SDK的账号系统(如果用第三方sdk封装了平台的sdk，账号系统如果是第三方sdk的，就设置用户类型为1)
     */
    LOGIN_USER_TYPE_SDK,
    /*
     * facebook用户
     */
    LOGIN_USER_TYPE_FACEBOOK,
    /*
     * 其他sns平台(非facebook)用户账号
     */
    LOGIN_USER_TYPE_SNS_PLATFORM,
    /*
     * 游戏平台用户账号
     */
    LOGIN_USER_TYPE_GAME_PLATFORM
} USER_TYPE;

typedef void(^LoginCallBackSuccess)(int,NSString *,LoginCallbackDataInfo *);
typedef void(^LoginCallBackFailed)(int,NSString *);

@interface UserWrapper : NSObject

/*!
 * @abstract 登陆回调方法.
 */
+ (void) onActionResult:(id)pPlugin retCode:(int)ret retMsg:(NSString*)msg;

//+ (NSString*) getLoginServerID;
//
//+ (NSString*) getLoginServerIP;

/*!
 * @abstract 登陆验证session.
 */
+ (void) getAccessToken:(NSMutableDictionary*)data target:(id)target sel:(SEL)sel;

/*!
 * @abstract 格式化验证token的数据格式.
 */
+(NSMutableDictionary *)formatLoginRequestData:(NSString *)pluginName token:(NSString *)token refresh_token:(NSString *)refresh_token pid:(NSString *)pid nickName:(NSString *)nickName userType:(NSString *)userType customData:(NSString *)customData loginTime:(NSString *)loginTime sign:(NSString *)sign platformSdkData:(NSString *)platformSdkData ext1:(NSString *)ext1 ext2:(NSString *)ext2 ext3:(NSString *)ext3;

/*!
 * @abstract 格式化验证token返回格式.
 */
+(LoginCallbackDataInfo *)handlerLoginDataFromServer:(NSString *)retString success:(LoginCallBackSuccess)success failed:(LoginCallBackFailed)failed;
@end
    
