//
//  GetOrderIdCallbackDataInfo.h
//  RSDK
//
//  Created by tonetchen on 15-3-4.
//

#import <Foundation/Foundation.h>

@interface GetOrderIdCallbackDataInfo : NSObject
@property(nonatomic,copy) NSString *orderId;
@property(nonatomic,copy) NSString *productName;
@property(nonatomic,copy) NSString *productId;
@property(nonatomic,copy) NSString *productCount;
@property(nonatomic,copy) NSString *coinNum;
@property(nonatomic,copy) NSString *productType;
@property(nonatomic,copy) NSString *rsdkServerName;
@property(nonatomic,copy) NSString *gameUserId;
@property(nonatomic,copy) NSString *platformOS;
@property(nonatomic,copy) NSString *gameServerId;
@property(nonatomic,copy) NSString *userId;
@property(nonatomic,copy) NSString *money;
@property(nonatomic,copy) NSString *privateData;


+(GetOrderIdCallbackDataInfo *)formatData:(NSMutableDictionary *)jsonData;
@end
