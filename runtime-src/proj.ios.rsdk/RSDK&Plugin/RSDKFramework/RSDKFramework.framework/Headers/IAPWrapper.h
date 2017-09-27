//
//  IAPWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-9-9.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GetOrderIdCallbackDataInfo.h"
#import <UIKit/UIKit.h>

typedef void(^GetOrderIdCallBackSuccess)(int,NSString *,GetOrderIdCallbackDataInfo *);
typedef void(^GetOrderIdCallBackFailed)(int,NSString *);

@interface IAPWrapper : NSObject<UIAlertViewDelegate>

+ (int) getNumber;

/*!
 * @abstract 发送商品角色等信息到RSDK-BaseServer获得RSDK订单号.
 */
+ (void)getPayOrderId:(NSMutableDictionary*)orderInfo target:(id)target action:(SEL)action;

typedef enum{
    PAYRESULT_SUCCESS = 0,
    PAYRESULT_FAIL,
    PAYRESULT_CANCEL,
    PAYRESULT_NETWORK_ERROR,
    PAYRESULT_PRODUCTIONINFOR_INCOMPLETE,
    PAYRESULT_INIT_SUCCESS,
    PAYRESULT_INIT_FAIL,
    PAYRESULT_NOW_PAYING,
    PAYRESULT_RECHARE_SUCCESS,
    PAYRESULT_DEVICE_FAIL
} PAY_SULT;

/*!
 * @abstract 支付回调方法.
 */
+ (void)onPayResult:(id)pPlugin retCode:(int)ret retMsg:(NSString*)msg;
+ (void)onPayResult:(id)pPlugin retCode:(int)ret products:(NSMutableDictionary*)products;
+(NSMutableDictionary *)formatPayRequestData:(NSString *)money gameUserId:(NSString *)gameUserId gameServerId:(NSString *)gameServerId  userId:(NSString *)userId productId:(NSString *)productId productName:(NSString *)productName coinNum:(NSString *)coinNum productType:(NSString *)productType productCount:(NSString *)productCount privateData:(NSString *)privateData;
+(GetOrderIdCallbackDataInfo *)handlerPayDataFromServer:(NSString *)retString success:(GetOrderIdCallBackSuccess)success failed:(GetOrderIdCallBackFailed)failed;

+ (NSString *)getEncryptStr:(NSMutableDictionary *)tempDict withPrivateKey:(NSString *)privateKey;
+ (NSString *)getBaseStr:(NSMutableDictionary *)tempDict;
+ (NSString *)encodeToken:(NSString *)tokenString;

@end
