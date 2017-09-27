//
//  PlatformCommon.h
//  rxzh
//
//  Created by hucanhua on 17/6/22.
//
//

#import <RSDKFramework/RWrapperManager.h>
#import <RSDKFramework/RSDKPlatform.h>

@interface PlatformCommon : NSObject<RSDKDelegate>

+ (instancetype)shareInstance;

//--------------------公用方法--------------------//
//游戏初始化
- (void)initGame;
//SDK初始化
- (void)sdkInit;
//SDK登录
- (void)sdkLogin;
//SDK登出
- (void)sdkLogout;
//SDK支付
- (void)sdkPay:(NSString*)jsonStr;
//创建角色
- (void)createRole:(NSString*)jsonStr;
//进入游戏
- (void)enterGame:(NSString*)jsonStr;
//角色升级
- (void)roleUpgrade:(NSString*)jsonStr;
//新手引导
- (void)custom:(NSString*)jsonStr;

//SDK回调cocos
- (void)sdkCallBack:(NSString*)eventtype response:(NSMutableDictionary*)dic token:(NSString*)token;

@end
