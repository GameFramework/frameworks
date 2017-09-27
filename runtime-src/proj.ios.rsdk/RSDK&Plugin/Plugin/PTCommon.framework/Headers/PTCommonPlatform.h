//
//  PTCommonPlatform.h
//  PTCommon
//
//  Created by 曹恩康 on 2016/12/22.
//  Copyright © 2016年 曹恩康. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "PTGameInfoVO.h"

/* dependence */

/* data */
@class PTUserVO;
@class PTUserInfo;
@class PTProductVO;
/**
 修改PTCountDB类为单例，已经不需要在此处@class进行‘set’
 @class PTCountDB;
 */

/* interface */
/**
 修改PTCountUtils类为单例，已经不需要在此处@class进行‘set’
 @class PTCountUtils;
 */

/* network */
/**
 隐藏PTGameClient类，直接调用PTCommonPlatform的‘用户部分相关接口’
 @class PTGameClient;
 */

/* tools */
@class PTDeviceInfo;

/* 回调Block */
// 成功的回调
typedef void(^PTCommonPlatformSucceeded)(id results);
// 失败的回调
typedef void(^PTCommonPlatformFailed)(NSError *error);

@interface PTCommonPlatform : NSObject

@property (nonatomic, strong) PTUserVO     *userVO;
@property (nonatomic, strong) PTGameInfoVO *gameInfoVO;
@property (nonatomic, assign) BOOL          isRecovery;
/**
 隐藏PTGameClient类，直接调用PTCommonPlatform的‘用户部分相关接口’
 @property (nonatomic, strong) PTGameClient *client;
 
 修改PTCountDB类为单例，已经不需要在此处进行‘set’
 @property (nonatomic, strong) PTCountDB    *countDB;
 
 修改PTCountUtils类为单例，已经不需要在此处@class进行‘set’
 @property (nonatomic, strong) PTCountUtils *countUtils;
 */

#pragma mark - 单例
/**
 GCD方式创建单例
 */
+ (PTCommonPlatform *)sharedInstance;

#pragma mark - PTGame Parameters & Methods
/**
 PTGame Parameters Resource
 
 @ ptGame_appId    统计ID
 @ ptGame_appKey   秘钥Key
 @ ptGame_language 版本语言
 @ ptGame_debug    当前模式
 */
@property (nonatomic, strong) NSString *ptGame_appId;
@property (nonatomic, strong) NSString *ptGame_appKey;
@property (nonatomic, strong) NSString *ptGame_language;
@property (nonatomic, assign) BOOL      ptGame_debug;

/**
 PTGame 初始化方法
 
 @ appId    统计ID
 @ appKey   秘钥Key
 @ language 版本语言
 @ debug    当前模式
 */
- (void)initPTGameWithAppId:(NSString *)appId withAppKey:(NSString *)appKey withLanguage:(NSString *)language withIsDebug:(BOOL)debug;


#pragma mark - PTTracker Parameters & Methods
/**
 PTTracker Parameters Resource
 
 @ ptTracker_appId    统计ID
 @ ptTracker_appKey   秘钥Key
 @ ptTracker_language 版本语言
 @ ptTracker_debug    当前模式
 @ ptTracker_biAgent  测试域名
 */
@property (nonatomic, strong) NSString *ptTracker_appId;
@property (nonatomic, strong) NSString *ptTracker_appKey;
@property (nonatomic, strong) NSString *ptTracker_language;
@property (nonatomic, assign) BOOL      ptTracker_debug;
@property (nonatomic, strong) NSString *ptTracker_biAgent;

/**
 PTTracker 初始化方法
 
 @ appId    统计ID
 @ appKey   秘钥Key
 @ language 版本语言
 @ debug    当前模式
 */
- (void)initPTTrackerWithAppId:(NSString *)appId withAppKey:(NSString *)appKey withLanguage:(NSString *)language withIsDebug:(BOOL)debug;


#pragma mark - Loading 视图
/**
 loading 显示等待视图
 
 @ view    所在视图层
 @ message 提示消息
 */
- (void)loadingWithView:(UIView *)view withMessage:(NSString *)message;

/**
 loading 关闭等待视图
 */
- (void)endLoading:(id)sender;


#pragma mark - 用户部分相关接口
/**
 游客账号升级
 
 @ username    用户名（必传参数）
 @ password    密码（必传参数）
 @ email       邮箱（选填）
 @ mobile      手机号码（选填）
 @ messageCode 验证码
 @ succeed     成功回调
 @ failed      失败回调
 */
- (void)guestUpgradeWithUsername:(NSString *)username password:(NSString *)password email:(NSString *)email mobile:(NSString *)mobile messageCode:(NSString *)messageCode succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 游客快速登录
 
 @ succeed 成功回调
 @ failed  失败回调
 */
- (void)guestLoginWithUsernamesucceed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 用户首次开启自动注册
 
 @ succeed 成功回调
 @ failed  失败回调
 */
- (void)guestLoginWithAutoRegister:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 用户登陆的方法
 
 @ username 用户名（必传参数）
 @ password 密码（必传参数）
 @ succeed  成功回调
 @ failed   失败回调
 */
- (void)loginWithUsername:(NSString *)username password:(NSString *)password encryptionPassword:(NSString *)encryptionPassword succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 用户注册的方法
 
 @ username    用户名（必传参数）
 @ password    密码（必传参数）
 @ email       邮箱（非必传参数）
 @ mobile      手机（非必传参数）
 @ messageCode 短信验证码（非必传参数）
 @ succeed     成功回调
 @ failed      失败回调
 */
- (void)registerWithUsername:(NSString *)username password:(NSString *)password email:(NSString *)email mobile:(NSString *)mobile  messageCode:(NSString *)messageCode succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 绑定邮箱的方法
 
 @ username 用户名（必传参数）
 @ email    邮箱（必传参数）
 @ password 密码（必传参数）
 @ succeed  成功回调
 @ failed   失败回调
 */
- (void)bindEmailWithUsername:(NSString *)username email:(NSString *)email password:(NSString *)password succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 修改密码的方法
 
 @ email   邮箱（必传参数）
 @ succeed 成功回调
 @ failed  失败回调
 */
- (void)resetPasswordWithEmail:(NSString *)email succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 开启应用时在上次关闭应用前未手动退出登录则自动登录
 
 @ token   令牌
 @ userId  用户id
 @ succeed 成功回调
 @ failed  失败回调
 */
- (void)loginWithRGameAccessToken:(NSString *)token userId:(NSString *)userId succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 使用GameCenter进行登录
 
 @ displayName 玩家昵称
 @ tpName      gamecenter
 @ tpUserId    玩家id
 @ bindflag    是否绑定
 @ succeed     成功回调
 @ failed      失败回调
 */
- (void)loginWithTpGameCenterDisplayName:(NSString *)displayName tpName:(NSString *)tpName tpUserId:(NSString *)tpUserId isbind:(BOOL)bindflag succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 使用第三方平台登录
 
 @ token    令牌
 @ tpName   平台名称
 @ tpUserId 玩家id
 @ bindflag 是否绑定
 @ succeed  成功回调
 @ failed   失败回调
 */
- (void)loginWithTpAccessToken:(NSString *)token tpName:(NSString *)tpName tpUserId:(NSString *)tpUserId isbind:(BOOL)bindflag succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 获取第三方支付网址
 
 @ olderId 订单id
 */
- (NSURLRequest *)getThirdPayUrl:(NSString *)olderId;

/**
 获取验证码
 
 @ appid    appid
 @ mobile   手机号码
 @ succeed  成功回调
 @ failed   失败回调
 */
- (void)getVerificationCodeWithAppId:(NSString *)appid
                     withMobilePhone:(NSString *)mobile
                             succeed:(PTCommonPlatformSucceeded)succeed
                              failed:(PTCommonPlatformFailed)failed;

/**
 绑定手机
 
 @ appid       appid
 @ username    用户名
 @ password    密码
 @ mobile      手机号码
 @ messageCode 短信验证码
 @ succeed     成功回调
 @ failed      失败回调
 */
- (void)bindMobilePhoneWithAppId:(NSString *)appid
                    withUserName:(NSString *)username
                    withPassword:(NSString *)password
                 withMobilePhone:(NSString *)mobile
                 withMessageCode:(NSString *)messageCode
                      withAction:(NSString *)action
                         succeed:(PTCommonPlatformSucceeded)succeed
                          failed:(PTCommonPlatformFailed)failed;

/**
 获取用户绑定的电话号码
 
 @ appid    appid
 @ username 用户名
 @ password 密码(加密)
 @ succeed  成功的回调
 @ failed   失败的回调
 */
- (void)getUserIsBindingMobilePhoneNumberWithAppId:(NSString *)appid
                                      withUserName:(NSString *)username
                                      withPassword:(NSString *)password
                                           succeed:(PTCommonPlatformSucceeded)succeed
                                            failed:(PTCommonPlatformFailed)failed;

/**
 根据电话号码获取用户信息
 
 @ appid   appid
 @ mobile  手机号码
 @ succeed 成功的回调
 @ failed  失败的回调
 */
- (void)getUserInfoByMobilePhoneNumberWithAppId:(NSString *)appid
                                withMobilePhone:(NSString *)mobile
                                        succeed:(PTCommonPlatformSucceeded)succeed
                                         failed:(PTCommonPlatformFailed)failed;

/**
 电话号码重置密码
 
 @ appid       appid
 @ mobile      手机号码
 @ messageCode 短信验证码
 @ password    重置新密码
 @ succeed     成功的回调
 @ failed      失败的回调
 */
- (void)resetPasswordByMobilePhoneWithAppId:(NSString *)appid
                            withMobilePhone:(NSString *)mobile
                            withMessageCode:(NSString *)messageCode
                               withPassword:(NSString *)password
                                    succeed:(PTCommonPlatformSucceeded)succeed
                                     failed:(PTCommonPlatformFailed)failed;

/**
 通过旧密码修改密码
 
 @ appid       appid
 @ username    用户名
 @ oldPassword 旧密码(加密)
 @ newPassword 新密码(明文)
 @ succeed     成功的回调
 @ failed      失败的回调
 */
- (void)byOldPasswordModifyPasswordWithAppId:(NSString *)appid
                                withUserName:(NSString *)username
                             withOldPassword:(NSString *)oldPassword
                             withNewPassword:(NSString *)newPassword
                                     succeed:(PTCommonPlatformSucceeded)succeed
                                      failed:(PTCommonPlatformFailed)failed;

/**
 验证电话号码和短信验证码是否匹配
 
 @ appid       appid
 @ mobile      手机号码
 @ messageCode 短信验证码
 @ succeed     成功的回调
 @ failed      失败的回调
 */
- (void)verifyMobileAndMessageCodeMatchWithAppId:(NSString *)appid
                                      withMobile:(NSString *)mobile
                                 withMessageCode:(NSString *)messageCode
                                         succeed:(PTCommonPlatformSucceeded)succeed
                                          failed:(PTCommonPlatformFailed)failed;

/**
 查询是否需要实名认证
 
 @ appid    平台ID
 @ username 用户名
 @ password 旧密码(加密)
 @ succeed  成功的回调
 @ failed   失败的回调
 */
- (void)isIdentificationWithAppId:(NSString *)appid withUserName:(NSString *)userName withPassword:(NSString *)password succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

/**
 实名信息提交
 
 @ appid      平台ID
 @ username   用户名
 @ password   旧密码(加密)
 @ realName   真实姓名
 @ identifyId 身份证号码
 @ succeed    成功的回调
 @ failed     失败的回调
 */
- (void)userIdentificationWithAppId:(NSString *)appid withUserName:(NSString *)userName withPassword:(NSString *)password withRealName:(NSString *)realName withIdentifyId:(NSString *)identifyId succeed:(PTCommonPlatformSucceeded)succeed failed:(PTCommonPlatformFailed)failed;

@end
