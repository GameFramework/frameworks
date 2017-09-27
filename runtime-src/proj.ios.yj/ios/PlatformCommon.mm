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
    [YiJieOnlineHelper initSDKWithListener:self];
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
    [YiJieOnlineHelper setLoginListener:self];
    [YiJieOnlineHelper login: @"login"];
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
    NSString *price = [NSString stringWithFormat:@"%@",dic[@"productRealPrice"]];
    NSString *productName = [NSString stringWithFormat:@"%@",dic[@"productName"]];
    NSString *noticeUrl = [NSString stringWithFormat:@"%@",dic[@"exs"][@"NoticeUrl"]];
    [YiJieOnlineHelper pay:[price intValue] :productName :1 :orderId :noticeUrl :self];
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
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLevel = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* zoneId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* zoneName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *tempDic = [[NSMutableDictionary alloc] init];
    [tempDic setValue:roleId forKey:@"roleId"];
    [tempDic setValue:roleName forKey:@"roleName"];
    [tempDic setObject:roleLevel forKey:@"roleLevel"];
    [tempDic setObject:zoneId forKey:@"zoneId"];
    [tempDic setObject:zoneName forKey:@"zoneName"];
    
    [tempDic setObject:@"0" forKey:@"balance"];
    [tempDic setObject:@"1" forKey:@"vip"];
    [tempDic setObject:@"无帮派" forKey:@"partyName"];
    [tempDic setObject:time forKey:@"roleCTime"];
    [tempDic setObject:time forKey:@"roleLevelMTime"];

    NSError* error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:tempDic options:NSJSONWritingPrettyPrinted error:&error];
    NSString* roleData = [[NSString alloc] initWithData:jsonData encoding: NSUTF8StringEncoding];
    [YiJieOnlineHelper setRoleData:roleData];
    [YiJieOnlineHelper setData:@"createrole" :roleData];
}

//进入游戏
- (void)enterGame:(NSString*)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----createRole == %@",dic);
    
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLevel = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* zoneId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* zoneName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *tempDic = [[NSMutableDictionary alloc] init];
    [tempDic setValue:roleId forKey:@"roleId"];
    [tempDic setValue:roleName forKey:@"roleName"];
    [tempDic setObject:roleLevel forKey:@"roleLevel"];
    [tempDic setObject:zoneId forKey:@"zoneId"];
    [tempDic setObject:zoneName forKey:@"zoneName"];
    
    [tempDic setObject:@"0" forKey:@"balance"];
    [tempDic setObject:@"1" forKey:@"vip"];
    [tempDic setObject:@"无帮派" forKey:@"partyName"];
    [tempDic setObject:time forKey:@"roleCTime"];
    [tempDic setObject:time forKey:@"roleLevelMTime"];
    
    NSError* error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:tempDic options:NSJSONWritingPrettyPrinted error:&error];
    NSString* roleData = [[NSString alloc] initWithData:jsonData encoding: NSUTF8StringEncoding];
    [YiJieOnlineHelper setData:@"enterServer" :roleData];
}

//角色升级
- (void)roleUpgrade:(NSString*)jsonStr {
    NSDictionary *dic = nil;
    if(jsonStr.length != 0){
        NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
        NSError *err;
        dic = [NSJSONSerialization JSONObjectWithData:jsonData options:NSJSONReadingMutableContainers error:&err];
    }
    NSLog(@"----createRole == %@",dic);
    
    NSString* roleId = [NSString stringWithFormat:@"%@",dic[@"roleId"]];
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLevel = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* zoneId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* zoneName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
    NSString* time = [NSString stringWithFormat:@"%@",dic[@"time"]];
    
    NSMutableDictionary *tempDic = [[NSMutableDictionary alloc] init];
    [tempDic setValue:roleId forKey:@"roleId"];
    [tempDic setValue:roleName forKey:@"roleName"];
    [tempDic setObject:roleLevel forKey:@"roleLevel"];
    [tempDic setObject:zoneId forKey:@"zoneId"];
    [tempDic setObject:zoneName forKey:@"zoneName"];
    
    [tempDic setObject:@"0" forKey:@"balance"];
    [tempDic setObject:@"1" forKey:@"vip"];
    [tempDic setObject:@"无帮派" forKey:@"partyName"];
    [tempDic setObject:time forKey:@"roleCTime"];
    [tempDic setObject:time forKey:@"roleLevelMTime"];
    
    NSError* error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:tempDic options:NSJSONWritingPrettyPrinted error:&error];
    NSString* roleData = [[NSString alloc] initWithData:jsonData encoding: NSUTF8StringEncoding];
    [YiJieOnlineHelper setData:@"levelup" :roleData];
}

//------------------------------------------------SDK回调------------------------------------------------//
#pragma mask - YiJieOnlineInitDelegate
- (void)onResponse:(NSString*)tag :(NSString*)value {
    NSLog(@"sfwarning  onResponse:%@,%@", tag, value);
}

#pragma mask - YiJieOnlineLoginDelegate
- (void)onLoginSuccess:(YiJieOnlineUser*)user :(NSString*)remain {
    NSString *channelId = user.channelId;
    NSString *uid = user.channelUserId;
    NSString *token = user.token;
    
    //NSString *channelId = [user.channelId stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    //NSString *uid = [user.channelUserId stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    //NSString *token = [user.token stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    token = [NSString stringWithFormat:@"%@|%@", token, channelId];
    
    NSLog(@"sfwarning  onLoginSuccess:%@", remain);
    NSLog(@"登录成功：%@    %@", uid, token);
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:@(0) forKey:@"result"];
    [dic setValue:@(PlatformFlag) forKey:@"platId"];
    [dic setObject:uid forKey:@"uid"];
    [self sdkCallBack:@"10001" response:dic token:token];
}


- (void)onLoginFailed:(NSString*)reason :(NSString*)remain {
    NSLog(@"sfwarning  onLoginFailed:%@", remain);
}

- (void)onLogout:(NSString*)remain {
    NSLog(@"切换账号");
    NSMutableDictionary *dic = [[NSMutableDictionary alloc] init];
    [dic setValue:@(0) forKey:@"result"];
    [self sdkCallBack:@"10002" response:dic token:@""];
}

#pragma mask - YiJieOnlinePayResultDelegate
- (void)onFailed:(NSString*)msg {
    NSLog(@"sfwarning  pay onFailed:%@", msg);
}

- (void)onSuccess:(NSString*)msg {
    NSLog(@"sfwarning  pay onSuccess:%@", msg);
}

- (void)onOderNo:(NSString*)msg {
    NSLog(@"sfwarning  pay onOderNo:%@", msg);
}

#pragma mask - YiJieOnlineExtendDelegate
- (void)onExtendResponse:(NSString*)tag :(NSString*)value {
    NSLog(@"ios demo onExtendResponse tag = %@  value = %@", tag, value);
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
