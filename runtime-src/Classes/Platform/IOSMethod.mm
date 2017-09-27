//
#import "PlatformCommon.h"

//sdk部分相关接口处理 eventtype为事件类型 params参数是json
void ios_eventTracking(const char* eventtype, const char* params)
{
    NSLog(@"-----eventtype == %s params == %s", eventtype, params);
    NSString *jsonStr = [NSString stringWithUTF8String:params];
    
    if (strcmp("10000", eventtype) == 0)
    {
        //初始化
        [[PlatformCommon shareInstance] sdkInit];
    }
    else if (strcmp("10001", eventtype) == 0)
    {
        //登录
        [[PlatformCommon shareInstance] sdkLogin];
    }
    else if (strcmp("10002", eventtype) == 0)
    {
        //登出
        [[PlatformCommon shareInstance] sdkLogout];
    }
    else if (strcmp("10003", eventtype) == 0)
    {
        //支付
        [[PlatformCommon shareInstance] sdkPay:jsonStr];
        
    }
    else if (strcmp("10004", eventtype) == 0)
    {
        //创建角色
        [[PlatformCommon shareInstance] createRole:jsonStr];
    }
    else if (strcmp("10005", eventtype) == 0)
    {
        //进入游戏
        [[PlatformCommon shareInstance] enterGame:jsonStr];
    }
    else if (strcmp("10006", eventtype) == 0)
    {
        //角色升级
        [[PlatformCommon shareInstance] roleUpgrade:jsonStr];
    }
    else if (strcmp("20001", eventtype) == 0)
    {
        //顾客事件
        [[PlatformCommon shareInstance] custom:jsonStr];
    }
}



