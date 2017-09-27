//
//  KXYXSDKManager.h
//  KXYXGameSDK
//
//  Created by 刘杰辉 on 2017/3/10.
//  Copyright © 2017年 刘杰辉. All rights reserved.
//

typedef enum WindowType {
    WindowTypeUser =0,      //我的
    WindowTypePay,          //支付
    WindowTypeGif,          //礼包
    WindowTypeService      //客服
}WindowType;
#import <UIKit/UIKit.h>

@interface KXYXSDKManager : NSObject

/**
 *  获取SDK单例
 *
 */
+ (instancetype)sharedVOneSDK;

/**
 设备支持方向 默认横屏
 */
@property (assign, nonatomic) UIInterfaceOrientationMask orientation;
/**
 *  获取登陆状态
 *
 */
+ (BOOL)isLogin;
/**
 *  退出登录时实现回调
 *  此方法用于监听个人中心中的退出按钮
 */
@property (strong, nonatomic) void(^logout)(void);

/**
 *  调用登陆界面
 *
 *  @param currentVC        发起调用的界面
 *  @param successBlock     登陆成功
 *  @param failBlock        登陆失败
 *
 */
- (void)login:(id)currentVC
      success:(void (^)(void))successBlock
      failure:(void (^)(NSString*))failBlock;
/**
 *  获取User信息
 *
 */
+ (NSString *)getUserName;//用户名
//+ (NSString *)getUserPassword;//用户密码 md5加密
+ (NSString *)getUserNickname;//用户昵称
+ (NSString *)getUserHaadimage;//用户头像

/**
 *  调用悬浮按钮
 *
 *  @param isShow        控制显示和隐藏悬浮按钮  默认为NO
 *
 */
- (void)showAssistiveView:(BOOL)isShow;

/**
 *  调用界面
 *
 *  @param type        打开的界面类型
 *
 */
- (void)showWindowType:(WindowType)type;


/**
 角色创建上报接口

 @param gameId 游戏id
 @param server_name 区服名称
 @param server_id 区服id
 @param create_role_time 角色创建时间 时间戳
 @param role_name 角色名
 @param level 等级
 @param completion 上报回调 error: 0->成功, 其他失败  info:信息描述
 */
- (void)roleCreateWithGameId:(NSInteger)gameId
                 server_name:(NSString *)server_name
                   server_id:(NSString *)server_id
            create_role_time:(NSString *)create_role_time
                   role_name:(NSString *)role_name
                       level:(NSInteger)level
                  completion:(void (^)(NSInteger error, NSString *info))completion;

/**
 角色升级上报接口

 */
- (void)upgradeWithGameId:(NSInteger)gameId
              server_name:(NSString *)server_name
                server_id:(NSString *)server_id
                role_name:(NSString *)role_name
                    level:(NSInteger)level
               completion:(void (^)(NSInteger error, NSString *info))completion;
/**
 支付返回错误编码
 WXERROR_PAYPARAM            = 1002,   //支付参数解析错误
 WXERROR_NOTINSTALL          = 1003,   //未安装微信
 WXERROR_PAY                 = 1004,   //支付失败
 WXCANCEL_PAY                = 1005,   //支付取消
 
 ALIPAYERROR_SCHEME          = 1101,     //scheme错误
 ALIPAYERROR_PAY             = 1102,     //支付错误
 ALIPAYCANCEL_PAY            = 1103,     //支付取消
 ALIPAYCANCEL_NOTINSTALL     = 1104,     //未安装支付宝
 ALIPAYERROR_PARTNER         = 1105,     //本地配置错误
 
 APPLEPAYERROR_PAY           = 1201,     //支付错误
 APPLEPAYCANCEL_PAY          = 1202,     //支付取消
 APPLEPAYCANCEL_NOTINSTALL   = 1203,     //不允许程序内付费购买
 APPLEPAYERROR_PARTNER       = 1204      //本地配置错误
 */


/**
 *  调用支付界面
 *
 *  @param currentVC        发起调用的界面
 *  @param payNum           支付金额
 *  @param goods            商品名称(可以不填)
 *  @param goods_desc       商品描述(可以不填)
 *  @param game_order_sn    游戏方订单号(充值进游戏必填, 充值到平台不用填)
 *  @param game_api_url     游戏方异步通知订单结果(充值进游戏必填, 充值到平台不用填)
 *  @param game_server_name 充值区服的名称(充值进游戏必填, 充值到平台不用填)
 *  @param role_name        充值角色名(充值进游戏必填, 充值到平台不用填)
 *  @param ext              拓展参数
 *  @param successBlock     支付成功
 *  @param failBlock        支付失败
 *
 */
- (void)toPay:(id)currentVC
          pay:(NSInteger)payNum
        goods:(NSString *)goods
   goods_desc:(NSString *)goods_desc
game_order_sn:(NSString *)game_order_sn
 game_api_url:(NSString *)game_api_url
game_server_name:(NSString *)game_server_name
    role_name:(NSString *)role_name
          ext:(NSString *)ext
      success:(void (^)(void))successBlock
      failure:(void (^)(NSInteger))failBlock;

/**
 *  回调入口
 *
 */
- (BOOL)handleOpenURL:(NSURL *) url
       standbyCallback:(void (^)(NSDictionary*))completionBlock;



/**
 提示用户 绑定手机
 */
- (void)showAlterView;


















@end
