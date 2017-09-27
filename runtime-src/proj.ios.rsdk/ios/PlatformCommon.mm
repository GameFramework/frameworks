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
    NSString *appKey     = @"c249a0-e5267-5587c-34688-549ffd72888";
    NSString *appSecret  = @"79175c06628dfb50850ad8fff7009a382795d323";
    NSString *privateKey = @"C7755A4EE5727B4FF71B55FC48303979";
    // 初始化RSDK
    [[RSDKPlatform sharedRsdk] initWithAppKey:appKey
                                    appSecret:appSecret
                                   privateKey:privateKey
                                  setDelegate:self
                                        Debug:NO];
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
    [[RSDKPlatform sharedRsdk] loginWithCustomParams:@""];
}

//SDK登出
- (void)sdkLogout {
    [[RSDKPlatform sharedRsdk] logout];
    //[[RSDKPlatform sharedRsdk] hideToolBar];
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
    NSString *price = [NSString stringWithFormat:@"%@",dic[@"productRealPrice"]];
    price = [NSString stringWithFormat:@"%d", [price intValue] / 100];
    NSString *productId = [NSString stringWithFormat:@"%@",dic[@"productId"]];
    NSString *productName = [NSString stringWithFormat:@"%@",dic[@"productName"]];
    
    NSString *roleId = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserRoleId"]];
    NSString *zoneId = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserServerId"]];
    NSString *roleName = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserRoleName"]];
    NSString *moneyAmount = [NSString stringWithFormat:@"%@",dic[@"exs"][@"GameMoneyAmount"]];
    
    NSMutableDictionary *paymentInfo = [[NSMutableDictionary alloc] init];
    [paymentInfo setObject:productId        forKey:@"Product_Id"];
    [paymentInfo setObject:price            forKey:@"Product_Price"];
    [paymentInfo setObject:productName      forKey:@"Product_Name"];
    
    [paymentInfo setObject:moneyAmount      forKey:@"Coin_Num"];
    [paymentInfo setObject:zoneId           forKey:@"Server_Id"];
    [paymentInfo setObject:roleId           forKey:@"Role_Id"];
    [paymentInfo setObject:roleName         forKey:@"Role_Name"];
    [paymentInfo setObject:orderId          forKey:@"private_data"];
    
    [[RSDKPlatform sharedRsdk] payWithProduct:paymentInfo];
}

//创建角色
- (void)createRole:(NSString *)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----createRole == %@",dic);
    
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* serverId = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *dicInfo = [[NSMutableDictionary alloc] init];
    [dicInfo setObject:roleId   forKey:@"gameUserId"];
    [dicInfo setObject:serverId forKey:@"serverId"];
    [dicInfo setObject:time     forKey:@"registerTime"];
    [[RSDKPlatform sharedRsdk] trackEvent:RSDK_Analytics_Install eventInfo:dicInfo];
}

//进入游戏
- (void)enterGame:(NSString*)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----enterGame == %@",dic);
    
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* serverId = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *dicInfo = [[NSMutableDictionary alloc] init];
    [dicInfo setObject:roleId   forKey:@"gameUserId"];
    [dicInfo setObject:serverId forKey:@"serverId"];
    [dicInfo setObject:time     forKey:@"registerTime"];
    [[RSDKPlatform sharedRsdk] trackEvent:RSDK_Analytics_SetGameUserInfo eventInfo:dicInfo];
}

//角色升级
- (void)roleUpgrade:(NSString*)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----roleUpgrade == %@",dic);
    
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* serverId = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *dicInfo = [[NSMutableDictionary alloc] init];
    [dicInfo setObject:roleId   forKey:@"gameUserId"];
    [dicInfo setObject:serverId forKey:@"serverId"];
    [dicInfo setObject:time     forKey:@"registerTime"];
    [[RSDKPlatform sharedRsdk] trackEvent:RSDK_Analytics_UserLeverUp eventInfo:dicInfo];
}

//新手引导
- (void)custom:(NSString*)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----roleUpgrade == %@",dic);
    
    NSString* serverId = [NSString stringWithFormat:@"%@",dic[@"serverId"]];
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* guideId = [NSString stringWithFormat:@"%@",dic[@"guideId"]];
    
    NSMutableDictionary *dicInfo = [[NSMutableDictionary alloc] init];
    [dicInfo setObject:roleId   forKey:@"gameUserId"];
    [dicInfo setObject:serverId forKey:@"serverId"];
    [dicInfo setObject:guideId  forKey:@"step"];
    [[RSDKPlatform sharedRsdk] trackEvent:RSDK_Analytics_BITutorial eventInfo:dicInfo];
}

#pragma mark - 用户回调方法
- (void)userCallBack:(NSMutableDictionary *)userInfo withCode:(kRSDK_UserCallBack_Code)code {
    switch (code) {
        case RSDK_UserCallBackFail: {
            NSLog(@"登录失败回调");
            NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
            [dic setValue:@(-1) forKey:@"result"];
            [self sdkCallBack:@"10001" response:dic token:@""];
        }
            break;
        case RSDK_LoginSuccess: {
            NSString *uid = [userInfo objectForKey:@"userId"];
            NSString *token  = [userInfo objectForKey:@"token"];
            NSString *channelId = [[RSDKPlatform sharedRsdk] getSubAppId];
            NSLog(@"登录成功：%@    %@", uid, token);
            
            uid = [NSString stringWithFormat:@"%@|%@", uid, channelId];
            
            NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
            [dic setValue:@(0) forKey:@"result"];
            [dic setValue:@(PlatformFlag) forKey:@"platId"];
            [dic setObject:channelId forKey:@"channelId"];
            [dic setObject:uid forKey:@"uid"];
            [self sdkCallBack:@"10001" response:dic token:token];
            [[RSDKPlatform sharedRsdk] showToolBar];
        }
            break;
        case RSDK_LogoutSuccess: {
            NSLog(@"登出成功回调");
            NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
            [dic setValue:@(0) forKey:@"result"];
            [self sdkCallBack:@"10002" response:dic token:@""];
        }
            break;
        case RSDK_BindSuccess: {
            NSLog(@"绑定成功回调");
        }
            break;
        case RSDK_AccountSwitchSuccess: {
            NSLog(@"切换成功回调");
        }
            break;
            
        default:
            break;
    }
}

#pragma mark - 支付回调方法
- (void)payCallBack:(NSMutableDictionary *)productInfo withCode:(kRSDK_PayCallBack_Code)code {
    switch (code) {
        case RSDK_PayFail: {
            NSLog(@"支付失败:%@", productInfo);
        }
            break;
        case RSDK_PaySuccess: {
            NSLog(@"支付成功:%@", productInfo);
        }
            break;
            
        default:
            break;
    }
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

@end
