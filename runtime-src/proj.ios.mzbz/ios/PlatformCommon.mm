//
//  PlatformCommon.m
//  tdht
//
//  Created by kevin on 16/10/25.
//
//

#import "PlatformCommon.h"
#import "KPlatformLogin.h"

#import "KXYXGameSDK.framework/Headers/KXYXSDKManager.h"

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
    [KXYXSDKManager sharedVOneSDK].logout = ^(){
        NSLog(@"SDK登出");
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
        [dic setValue:@(0) forKey:@"result"];
        [self sdkCallBack:@"10002" response:dic token:@""];
    };
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
    [[KXYXSDKManager sharedVOneSDK] login:self success:^{
        NSString* userId = [KXYXSDKManager getUserName];
        NSLog(@"登录成功：%@", userId);
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
        [dic setValue:@(0) forKey:@"result"];
        [dic setValue:@(PlatformFlag) forKey:@"platId"];
        [dic setObject:userId forKey:@"uid"];
        [self sdkCallBack:@"10001" response:dic token:@""];
    } failure:^(NSString * failStr) {
        NSLog(@"登录失败：%@", failStr);
        NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
        [dic setValue:@(-1) forKey:@"result"];
        [self sdkCallBack:@"10001" response:dic token:@""];
    }];
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
    
    NSString *productRealPrice = [NSString stringWithFormat:@"%@",dic[@"productRealPrice"]];
    NSInteger money = [productRealPrice integerValue] / 100;
    
    NSString *productName = [NSString stringWithFormat:@"%@",dic[@"productName"]];
    NSString *productDes = [NSString stringWithFormat:@"%@",dic[@"description"]];
    NSString *orderId = [NSString stringWithFormat:@"%@",dic[@"myOrderId"]];
    NSString *noticeUrl = [NSString stringWithFormat:@"%@",dic[@"exs"][@"NoticeUrl"]];
    NSString *serverName = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserServerName"]];
    NSString *roleName = [NSString stringWithFormat:@"%@",dic[@"exs"][@"UserRoleName"]];
    
    [[KXYXSDKManager sharedVOneSDK] toPay:self pay:money goods:productName goods_desc:productDes game_order_sn:orderId game_api_url:noticeUrl game_server_name:serverName role_name:roleName ext:@"" success:^{
        NSLog(@"支付成功");
    } failure:^(NSInteger failcode) {
        NSLog(@"支付失败==%ld", (long)failcode);
    }];
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
    
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLv = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* serverId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* serverName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    [[KXYXSDKManager sharedVOneSDK] roleCreateWithGameId:27 server_name:serverName server_id:serverId create_role_time:time role_name:roleName level:[roleLv integerValue] completion:^(NSInteger error, NSString *info) {
        if (error) {
            NSLog(@"创建角色 error = %ld, info = %@", (long)error, info);
        } else {
            NSLog(@"创建角色成功");
        }
    }];
}

//进入游戏
- (void)enterGame:(NSString*)jsonStr {
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
    
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLv = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* serverId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* serverName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
    
    [[KXYXSDKManager sharedVOneSDK] upgradeWithGameId:27 server_name:serverName server_id:serverId role_name:roleName level:[roleLv integerValue] completion:^(NSInteger error, NSString *info) {
        if (error) {
            NSLog(@"升级 error = %ld, info = %@", (long)error, info);
        } else {
            NSLog(@"角色升级成功");
        }
    }];
}

//------------------------------------------------SDK回调Cocos------------------------------------------------//
//SDK回调
- (void) sdkCallBack:(NSString*)eventtype response:(NSMutableDictionary*)dic token:(NSString*)token {
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
