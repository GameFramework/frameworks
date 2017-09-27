//
//  LoginCallbackDataInfo.h
//  libRSDKPluginIOS
//
//  Created by tonetchen on 15-2-6.
//

/*
 标准化登录token验证的结果部分
 从插件中抽象出来
 */

#import <Foundation/Foundation.h>

@interface LoginCallbackDataInfo : NSObject
@property(nonatomic,copy) NSString *pid;
@property(nonatomic,copy) NSString *pid_prefix;
@property(nonatomic,copy) NSString *nickname;
@property(nonatomic,copy) NSString *token;
@property(nonatomic,copy) NSString *token_expire;
@property(nonatomic,copy) NSString *token_refresh;
@property(nonatomic,copy) NSString *server_ext_param;
@property(nonatomic,copy) NSString *source;
@property(nonatomic,copy) NSString *user_type;
@property(nonatomic,copy) NSString *custom_data;
@property(nonatomic,copy) NSString *identity_auth;

+(LoginCallbackDataInfo *)formatData:(NSMutableDictionary *)jsonData;
@end
