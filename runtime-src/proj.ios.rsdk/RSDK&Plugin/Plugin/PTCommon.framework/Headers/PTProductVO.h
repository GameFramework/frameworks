//
//  PTProductVO.h
//  PTCommon
//
//  Created by 杨建亚 on 14-4-19.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PTProductVO : NSObject

@property (nonatomic, strong) NSString *productID;
@property (nonatomic, strong) NSString *productName;
@property (nonatomic, strong) NSString *productDescription;
@property (nonatomic, strong) NSString *serverId;
@property (nonatomic, strong) NSString *gameExtra;
@property (nonatomic, strong) NSString *currency;
@property (nonatomic, strong) NSString *bundleIdentifier;

@property (nonatomic) float amount;
@property (nonatomic) int   gameCoinAmount;
@property (nonatomic) int   count;

@end
