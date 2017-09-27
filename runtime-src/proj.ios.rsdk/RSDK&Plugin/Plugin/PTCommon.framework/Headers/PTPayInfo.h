//
//  PTPayInfo.h
//  PTCommon
//
//  Created by 陈勋华 on 16/6/9.
//  Copyright © 2016年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PTPayInfo : NSObject
/**
 用户ID
 */
@property(nonatomic, copy) NSString *user_id;
/**
 角色ID
 */
@property(nonatomic, copy) NSString *role_id;
/**
 用户等级
 */
@property(nonatomic, copy) NSString *role_level;
/**
 vip等级
 */
@property(nonatomic, copy) NSString *vip_level;
/**
 区服id
 */
@property(nonatomic, copy) NSString *server_id;
/**
 商品名称
 */
@property(nonatomic, copy) NSString *product_name;
/**
 商品类型
 */
@property(nonatomic, copy) NSString *product_type;
/**
 商品数量
 */
@property(nonatomic, copy) NSString *product_count;
/**
 单价
 */
@property(nonatomic, copy) NSString *product_price;
/**
 总价
 */
@property(nonatomic, copy) NSString *ammount;
/**
 币种
 */
@property(nonatomic, copy) NSString *currency;
/**
 订单号
 */
@property(nonatomic, copy) NSString *order_id;
@end
