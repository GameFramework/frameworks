//
//  PTCountUtils.h
//  PTCommon
//
//  Created by 陈勋华 on 16-4-24.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PTUserInfo;

/**
 构造BI参数
 为了区分‘新手引导’和‘在线统计’构造参数时使用
 */
typedef NS_ENUM(NSUInteger, STRUCTURAL_BI_PARAMETERS) {
    STRUCTURAL_NEWBIEGUIDE_PARAMETERS = 0,  // 新手引导
    STRUCTURAL_ONLINE_PARAMETERS,           // 在线统计
}; // 统计类型

@interface PTCountUtils : NSObject

#pragma mark - 单例
+ (PTCountUtils *)sharedInstance;

#pragma mark - debug flag
@property (nonatomic) BOOL debugFlag;

#pragma mark - SetGameInfo 统计
/**
 SetGameInfo 统计 获取角色信息成功后调用
 */
- (void)countForSetGameUserInfo:(PTUserInfo *)userInfo;

#pragma mark - 新手引导 统计
/**
 新手引导 统计
 */
- (void)countForBITutorial:(PTUserInfo *)userInfo;

#pragma mark - 在线统计 统计
/**
 在线统计 统计
 */
- (void)countForBIHeartBeat:(PTUserInfo *)userInfo;

@end
