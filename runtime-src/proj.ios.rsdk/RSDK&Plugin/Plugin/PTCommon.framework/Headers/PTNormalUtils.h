//
//  PTNormalUtils.h
//  PTCommon
//
//  Created by 曹恩康 on 2016/12/16.
//  Copyright © 2016年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface PTNormalUtils : NSObject

#pragma mark - 用户输入框限制-正则表达式
/**
 检测用户名是否合法
 */
+ (BOOL)isValidateUserName:(NSString *)userName;

/**
 检测密码是否合法
 */
+ (BOOL)isValidatePwd:(NSString *)password;

/**
 检测邮箱是否合法
 */
+ (BOOL)isValidateEmail:(NSString *)email;

/**
 检测国内手机是否合法
 */
+ (BOOL)isValidatePhone:(NSString *)phone;

/**
 检测短信验证码是否合法
 */
+ (BOOL)isValidateSMS:(NSString *)sms;

/**
 检测身份证号码是否合法
 */
+ (BOOL)isValidateIdentificationCard:(NSString *)idCard;

/**
 检测身份证姓名是否合法
 */
+ (BOOL)isValidateChinese:(NSString *)chinese;

#pragma mark - 数据类型转换
/**
 将字典转换成Json字符串的格式
 */
+ (NSString *)jsonStringFromDictionary:(NSMutableDictionary *)dic;

/**
 将Json字符串转换成字典的格式
 */
+ (NSMutableDictionary *)dictionaryFromJsonString:(NSString *)jsonString;

/**
 将NSData数据转换成NSDictionary格式
 */
+ (NSDictionary *)jsonDictionaryFromData:(NSData *)data;

/**
 将数组转换成Json字符串
 */
+ (NSString *)storeAryToJson:(NSMutableArray *)array;

/**
 将Json字符串转换成数组
 */
+ (NSMutableArray *)parsingJsonToArray:(NSString *)JsonString;

/**
 过滤字符串String安全处理
 */
+ (NSString *)filterString:(NSString *)string;

/**
 判断字符串是否为空
 */
+ (BOOL)isBlankString:(NSString *)string;

/**
 encode
 请求的参数里有特殊符号比如“+”等等，而如果没有Encode的话那么传过去的还是” ”，而实际上是%2B
 */
+ (NSString *)encodeString:(NSString *)unencodeString;

#pragma mark - 'MD5'加密方法
/**
 MD5 加密 16进制
 */
+ (NSString *)md5HexDigest:(NSString *)string;

#pragma mark - 网络请求参数通过'Base64'加密生成字段key'a'=value'base64加密字符串'
/**
 网络请求参数通过‘Base64’加密生成字段key'a'=value'base64加密字符串'
 
 @ params 参数
 @ appKey 秘钥
 */
+ (NSMutableDictionary *)base64Encryption:(NSMutableDictionary *)params
                               withAppKey:(NSString *)appKey;

#pragma mark - 'Base64'加密
/**
 Base64 加密
 */
+ (NSString *)dataBase64Encoding:(NSData *)data withLineLength:(unsigned int)lineLength;

#pragma mark - 国际化语言
/**
 国际化语言
 根据所传的参数key找到对应的翻译，默认语言为英语'en'
 */
+ (NSString *)localizedStringForKey:(NSString *)key;

#pragma mark - 钥匙串存储
/**
 用户名历史记录存储 处理
 老版本的钥匙串中不存在userId字段，所以还是采取老方式userName作为钥匙串的用户标识
 @ userType 用户类型
 @ userName 用户名
 @ password 密码
 */
+ (void)historyUserListSaveType:(NSString *)userType
                       userName:(NSString *)userName
                       password:(NSString *)password;

#pragma mark - 钥匙串存储(新版)
/**
 用户名历史记录存储 处理
 新版本用户名、绑定的手机号码和邮箱都可以作为用户名登录，所以采取了userId作为钥匙串的用户标识
 @ userType 用户类型
 @ userName 用户名
 @ password 密码
 @ userId   用户ID
 */
+ (void)historyUserListSaveType:(NSString *)userType
                       userName:(NSString *)userName
                       password:(NSString *)password
                         userId:(NSString *)userId;

@end
