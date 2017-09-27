//
//  RSDKLog.h
//  RSDKFramework
//
//  Created by tonetchen on 15/11/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RSDKLog : NSObject

/*!
* @abstract 弹出RSDK内提示消息.
*/
+(void)alertMessage:(NSString *)message;
+(void)alertMessageHud:(NSString *)message;

/*!
 * @abstract RSDK格式化输出日志.
 */
+(void)printLog:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
+(void)writeLog:(NSString *)title content:(NSString *)content className:(NSString *)className functionName:(NSString *)functionName;

/*!
 * @abstract RSDK日志类型：错误.
 */
+(void)rsdkErrorLog:(NSString *)messgae, ... NS_FORMAT_FUNCTION(1,2);

/*!
 * @abstract RSDK日志类型：警告.
 */
+(void)rsdkWarnLog:(NSString *)messgae, ... NS_FORMAT_FUNCTION(1,2);

/*!
 * @abstract RSDK日志类型：正常.
 */
+(void)rsdkNormalLog:(NSString *)messgae, ... NS_FORMAT_FUNCTION(1,2);

/*
 *loading
 */
+ (void)showRMBProgressHUD:(NSString *)showMessage;
+ (void)hideRMBprogressHUD;

/*!
 * @brief RSDK Debug 模式
 */
+ (void)setDebugMode:(BOOL)debug;
@end
