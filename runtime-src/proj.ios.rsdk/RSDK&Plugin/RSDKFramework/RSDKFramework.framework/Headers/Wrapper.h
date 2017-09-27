//
//  Wrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-8-29.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>

#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue &0xFF00) >>8))/255.0 blue:((float)(rgbValue &0xFF))/255.0 alpha:1.0]

@interface Wrapper : NSObject

+(void) setAppParam:(const char*)appKey AppSecret:(const char*)appSeceret PrivateKey:(const char*)privateKey OauthLoginServer:(const char*)oauthLoginServer;
+(Wrapper*)getWrapper;
/*!
 * @abstract 获得developInfo的配置.
 */
+(NSMutableDictionary*) getDeveloperInfo;

+(NSString*)pluginDecode:(NSString *)encodeString;

+(NSString*)dictToNSString:(NSMutableDictionary*)dict;

/*!
 * @abstract 获取ChannelId.
 */
+(NSString*)getChannelId;

+(NSString*)getCustomParam;

+ (BOOL) networkReachable;

+(void)analysisDeveloperInfo;

+(NSMutableDictionary*)analysisSupportPlugin;

+(NSString *)getPluginIdFromClassName:(NSString *) className;

+(NSString *)getPluginNameFromClassName:(NSString *) className;

+(NSString *)getChannelFromSDKName:(NSString *) pluginName;

+(NSString *)getSDKParm_r_nofify_url:(NSString *)pluginName;

+(NSString *)getSDKParm_r_order_url:(NSString *)pluginName;

+(NSString *)getSDKParm_r_sdk_platform:(NSString *)pluginName;

+(NSString *)getSDKParm_r_login_rsdkserver_version:(NSString *)pluginName;

+(NSString *)getChannelParm_r_big_app_id:(NSString *)pluginName;

+(NSString *)getChannelParm_r_sub_app_id:(NSString *)pluginName;
/*!
 * @abstract 初始化回调方法.
 */
+(void)onInitResultCode:(int)ret retMsg:(NSString*)msg;

/*!
 * @abstract 获得多插件的shouName等配置.
 */
+(NSMutableDictionary*) getShowNameInfo:(NSString*)xmlKeyName;

+ (NSString *)getAppKey;

/*!
 * @abstract 获取设备唯一标示.
 */
+ (NSString *)getDeviceIdentifier;

/**
 获取RSDK 协议的版本号
 
 @return 版本号
 */
+ (NSString *)getRSDKVersion;

@end
