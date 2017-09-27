//
//  PTTrackerPlatform.h
//  PTTracker
//
//  Created by 曹恩康 on 2016/12/26.
//  Copyright © 2016年 曹恩康. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <PTCommon/PTCommon.h>

/**
 统计类型
 
 'BiAgent'目前是四种统计: 1.Open 2.SetGameInfo 3.新手引导 4.在线统计
 注:由于Open统计是启动应用的时候自动调用，无需手动调用
 
 '热云'目前是六种统计: 1.开启数据统计 2.注册成功后统计 3.登陆成功后统计 4.开始付费时统计 5.付费完成后统计 6.自定义统计
 */
typedef NS_ENUM(NSUInteger, PTSTATISTICALTYPE) {
    PTSTATISTICAL_SETGAMEINFO_TYPE = 0,  // SetGameInfo
    PTSTATISTICAL_NEWBIEGUIDE_TYPE,      // 新手引导
    PTSTATISTICAL_ONLINE_TYPE,           // 在线统计
    PTSTATISTICAL_REYUN_REGISTE,         // 热云->注册成功后调用
    PTSTATISTICAL_REYUN_LOGIN,           // 热云->登陆成功后调用
    PTSTATISTICAL_REYUN_PAYMENTSTART,    // 热云->开始付费时调用
    PTSTATISTICAL_REYUN_PAYMENT,         // 热云->付费完成后调用
    PTSTATISTICAL_REYUN_EVENT,           // 热云->自定义事件
}; // 统计类型

@interface PTTrackerPlatform : NSObject

#pragma mark - 热云
/**
 热云 Parameters Resource
 
 @ reYunAppKey    热云AppKey
 @ reYunChannelId 热云渠道ID
 */
@property (nonatomic, strong) NSString *reYunAppKey;
@property (nonatomic, strong) NSString *reYunChannelId;

#pragma mark - 单例
/**
 GCD方式创建单例
 */
+ (PTTrackerPlatform *)sharedInstance;

#pragma mark - PTTracker 初始化方法
/**
 PTTracker 初始化方法
 
 @ appId          统计ID
 @ appKey         秘钥Key
 @ language       版本语言
 @ reYunAppKey    热云AppKey
 @ reYunChannelId 热云渠道ID
 @ debug          当前模式
 */
- (void)initPTTrackerWithAppId:(NSString *)appId
                    withAppKey:(NSString *)appKey
                  withLanguage:(NSString *)language
               withReYunAppKey:(NSString *)reYunAppKey
            withReYunChannelId:(NSString *)reYunChannelId
                   withIsDebug:(BOOL)debug;

#pragma mark - 统计
/**
 统计
 
 @ userInfo        统计参数
 @ statisticalType 统计类型
 */
+ (void)statistics:(PTUserInfo *)userInfo statisticalType:(PTSTATISTICALTYPE)statisticalType;

@end
