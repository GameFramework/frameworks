//
//  PTUserInfo.h
//  PTCommon
//
//  Created by 陈勋华 on 16/6/9.
//  Copyright © 2016年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PTUserInfo : NSObject
/**
 用户ID
 */
@property(nonatomic, copy) NSString *user_id;
/**
 用户名
 */
@property(nonatomic, copy) NSString *user_name;
/**
 角色ID
 */
@property(nonatomic, copy) NSString *game_user_id;
/**
 角色名称
 */
@property(nonatomic, copy) NSString *game_user_name;
/**
 用户等级
 */
@property(nonatomic, copy) NSString *game_user_level;
/**
 vip等级
 */
@property(nonatomic, copy) NSString *vip_level;
/**
 注册时间
 */
@property(nonatomic, copy) NSString *register_time;
/**
 性别
 */
@property(nonatomic, copy) NSString *gender;
/**
 年龄
 */
@property(nonatomic, copy) NSString *age;
/**
 区服id
 */
@property(nonatomic, copy) NSString *game_server_id;
/**
 区服名称
 */
@property(nonatomic, copy) NSString *game_server_name;
/**
 用户当前新手引导的步数
 */
@property(nonatomic, copy) NSString *firstexperience_step;
/**
 用户注册天数
 */
@property(nonatomic, copy) NSString *user_days;
/**
 统计ID
 */
@property(nonatomic, copy) NSString *channel;
/**
 获取设备唯一标示
 */
@property(nonatomic, copy) NSString *deviceIdentifier;

#pragma mark - ReYun
/**
 热云 账户ID
 */
@property(nonatomic, copy) NSString *reYun_accountId;
/**
 热云 商品ID
 */
@property(nonatomic, copy) NSString *reYun_transactionId;
/**
 热云 支付类型
 */
@property(nonatomic, copy) NSString *reYun_paymentType;
/**
 热云 货币类型
 */
@property(nonatomic, copy) NSString *reYun_currencyType;
/**
 热云 金额
 */
@property(nonatomic, assign) float   reYun_currencyAmount;
/**
 热云 自定义事件
 */
@property(nonatomic, copy) NSString *reYun_eventName;

@end
