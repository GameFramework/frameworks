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
}

//SDK初始化
- (void)sdkInit {
}

//SDK登录
- (void)sdkLogin {
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
    NSString* serverId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* serverName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
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
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLevel = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* serverId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* serverName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
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
    NSString* roleName = [NSString stringWithFormat:@"%@",dic[@"roleName"]];
    NSString* roleLevel = [NSString stringWithFormat:@"%@",dic[@"level"]];
    NSString* serverId  = [NSString stringWithFormat:@"%@",dic[@"serverNo"]];
    NSString* serverName = [NSString stringWithFormat:@"%@",dic[@"serverName"]];
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
