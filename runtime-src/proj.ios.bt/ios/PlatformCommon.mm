//
//  PlatformCommon.m
//  tdht
//
//  Created by kevin on 16/10/25.
//
//

#import "PlatformCommon.h"
#import "KPlatformLogin.h"

@implementation PlatformCommon

+ (instancetype)shareInstance {
    static PlatformCommon* platformcommon;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        platformcommon = [PlatformCommon new];
    });
    return platformcommon;
}

//游戏初始化
- (void)initGame {
    KPlatformLogin::getInstance()->setPlatformId(PlatformFlag);
    
    [[GameCenterSDK sharedGame] initWithPid:@"11699" Scheme:@"rxzh" appKey:@"f17354c8ae8b7a1cb5aab8f285c22c69" delegate:self success:^(initReturnCode code) {
        NSLog(@"初始化成功");
    } fialed:^(id error) {
        NSLog(@"初始化失败");
    }];
}

//SDK初始化
- (void)sdkInit {
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:@(0) forKey:@"result"];
    [dic setValue:@(PlatformFlag) forKey:@"platId"];
    [self sdkCallBack:@"10000" response:dic token:@""];
}

//SDK登录
- (void)sdkLogin {
    [[GameCenterView sharedView] addLoginView:self];
}

//SDK登出
- (void)sdkLogout {
}

//SDK支付
- (void)sdkPay:(NSString *)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----pay == %@",dic);
    
    NSString *orderId = [NSString stringWithFormat:@"%@",dic[@"myOrderId"]];
    NSString *productRealPrice = [NSString stringWithFormat:@"%@",dic[@"productRealPrice"]];
    int money = [productRealPrice intValue] / 100;
    NSString *amount = [NSString stringWithFormat:@"%d", money];
    NSString *serverId = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserServerId"]];
    [[GameCenterView sharedView] addPayView:self amount:amount serverid:serverId extendsinfo:orderId];
}

//创建角色
- (void)createRole:(NSString *)jsonStr {
}

//进入游戏
- (void)enterGame:(NSString*)jsonStr {
}

//角色升级
- (void)roleUpgrade:(NSString*)jsonStr {
}

//------------------------------------------------SDK回调------------------------------------------------//
#pragma mask - SDKLoginViewDelegate
//登录回调
- (void)loginData:(NSDictionary *)dict {
    NSString *userId = [NSString stringWithFormat:@"%@",dict[@"data"][@"uid"]];
    NSString *token = [NSString stringWithFormat:@"%@",dict[@"data"][@"token"]];
    NSString *userName = [NSString stringWithFormat:@"%@",dict[@"data"][@"username"]];
    NSString *uid = [NSString stringWithFormat:@"%@|%@", userName, userId];
    NSLog(@"登录成功：%@    %@", uid, token);
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:@(0) forKey:@"result"];
    [dic setValue:@(PlatformFlag) forKey:@"platId"];
    [dic setObject:uid forKey:@"uid"];
    [self sdkCallBack:@"10001" response:dic token:token];
}

#pragma mask - SDKPayViewDelegate
// 支付回调
- (void)sdk_pay:(payReturnCode)code {
    if (code == pay_success) {
        NSLog(@"支付成功");
    }
    else {
        NSLog(@"支付失败");
    }
}

// 关闭支付界面
- (void)sdk_close {
    NSLog(@"关闭支付");
}

#pragma mask - SDKMineViewDelegate
//切换账号
- (void)switchAccount {
    NSLog(@"切换账号");
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:@(0) forKey:@"result"];
    [self sdkCallBack:@"10002" response:dic token:@""];
}


//------------------------------------------------SDK回调Cocos------------------------------------------------//
//SDK回调
- (void)sdkCallBack:(NSString*)eventtype response:(NSMutableDictionary*)dic token:(NSString*)token {
    NSLog(@"----SDK回调 %@  %@", eventtype, token);
    NSError *error = nil;
    NSString *jsonStr;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dic options:NSJSONWritingPrettyPrinted error:&error];
    if([jsonData length] > 0 && error == nil) {
        jsonStr = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSLog(@"data:%@",jsonStr);
    }
    
    KPlatformLogin::getInstance()->callEventToLua([eventtype UTF8String], [jsonStr UTF8String], [token UTF8String]);
}

//appdelegate代理方法
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    NSString *scheme = [GameCenterSDK getScheme];
    if ([url.scheme isEqualToString:scheme]) {
        [[NSNotificationCenter defaultCenter] postNotificationName:@"PayResult" object:nil userInfo:@{@"result":url}];
    }
    
    return YES;
}

@end
