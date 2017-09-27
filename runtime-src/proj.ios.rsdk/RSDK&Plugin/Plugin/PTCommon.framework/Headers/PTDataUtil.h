//
//  PTDataUtil.h
//  PTCommon
//
//  Created by 杨建亚 on 14-4-19.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PTDataUtil : NSObject

#pragma mark - 存储字符串
+ (BOOL)storeObjectWithKey:(NSString *)key value:(NSString *)value;

#pragma mark - 存储对象
+ (BOOL)storeObjectWithKey:(NSString *)key objectValue:(id)value;
+ (id)objectOfKey:(NSString *)key;
+ (id)objectOfKeyArr:(NSString *)key;

#pragma mark - 存储已经绑定的类型
+ (NSMutableArray *)bindsARR;
+ (void)setbindsARR:(NSMutableArray *)bindsARR;

#pragma mark - 用户历史记录存储
+ (NSMutableArray *)historyUserList;
+ (void)sethistoryUserList:(NSMutableArray *)userList;

#pragma mark - 是否是第一次登录
+ (NSString *)isFirstLogin;
+ (void)setIsFirstLogin:(NSString *)isFirstLogin;

#pragma mark - 登录用户类型
+ (NSString *)userType;
+ (void)setUserType:(NSString *)userType;

#pragma mark - 是否游客登录
+ (NSString *)isGuestlogin;
+ (void)setIsGuestlogin:(NSString *)IsGuestlogin;

#pragma mark - userId
+ (NSString *)userId;
+ (void)setUserId:(NSString *)userId;

#pragma mark - loginToken
+ (NSString *)loginToken;
+ (void)setLoginToken:(NSString *)loginToken;

#pragma mark - displayName
+ (NSString *)displayName;
+ (void)setDisplayName:(NSString *)displayName;

#pragma mark - userName
+ (NSString *)userName;
+ (void)setUserName:(NSString *)userName;

#pragma mark - password
+ (NSString *)password;
+ (void)setPassword:(NSString *)password;

#pragma mark - email
+ (NSString *)email;
+ (void)setEmail:(NSString *)email;

#pragma mark - mobile
+ (NSString *)mobile;
+ (void)setMobile:(NSString *)mobile;

#pragma mark - tpName
+ (NSString *)tpName;
+ (void)setTpName:(NSString *)tpName;

#pragma mark - tpUserId
+ (NSString *)tpUserId;
+ (void)setTpUserId:(NSString *)tpUserId;

#pragma mark - chartboostId
+ (NSString *)chartboostId;
+ (void)setchartboostId:(NSString *)chartboostId;

#pragma mark - chartboostSignature
+ (NSString *)chartboostSignature;
+ (void)setchartboostSignature:(NSString *)chartboostSignature;

@end
