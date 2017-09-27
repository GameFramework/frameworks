//
//  ShareWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-11-12.
//  Copyright (c) 2014年 zhangbin. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    SHARERESULT_SUCCESS = 0,
    SHARERESULT_FAIL,
    SHARERESULT_CANCEL,
    SHARERESULT_NETWORK_ERROR
} SHARE_ACTION_RET;

@interface ShareWrapper : NSObject

/*!
 * @abstract 分享回调方法.
 */
+(void)onShareResult:(id)pPlugin retCode:(int)ret retMsg:(NSString* )msg;

@end
