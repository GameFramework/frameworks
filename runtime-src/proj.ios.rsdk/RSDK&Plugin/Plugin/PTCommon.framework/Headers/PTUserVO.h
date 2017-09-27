//
//  PTUserVO.h
//  PTCommon
//
//  Created by 杨建亚 on 14-4-19.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PTUserVO : NSObject

@property (nonatomic, strong) NSString *user_id;
@property (nonatomic, strong) NSString *user_name;
@property (nonatomic, strong) NSString *login_token;
@property (nonatomic, strong) NSString *display_name;
@property (nonatomic, strong) NSString *tp_name;
@property (nonatomic, strong) NSString *tp_uid;
@property (nonatomic, strong) NSString *firstUserName;
@property (nonatomic, strong) NSString *firstPassWord;

- (id)initWithDictionary:(NSDictionary *)dic;

@end
