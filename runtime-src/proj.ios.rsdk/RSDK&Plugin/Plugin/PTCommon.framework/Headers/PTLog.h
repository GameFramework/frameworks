//
//  PTLog.h
//  PTCommon
//
//  Created by 曹恩康 on 2017/1/17.
//  Copyright © 2017年 曹恩康. All rights reserved.
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT void PTGameLog(NSString *format, ...);

FOUNDATION_EXPORT void PTTrackerLog(NSString *format, ...);


/**
 PTGame分级日志
 
 Debug == YES; 输出全部日志
 
 2.Operation   操作日志 凡用户操作的步骤都能输出
 3.NetworkData 网络数据日志输出
 4.Warning     警告日志
 5.Error       错误日志
 */
#pragma mark - 操作日志
/**
 操作日志
 */
FOUNDATION_EXPORT void PTGameOperationLog(NSString *format, ...);

#pragma mark - 网络数据日志
/**
 网络数据日志
 */
FOUNDATION_EXPORT void PTGameNetworkDataLog(NSString *format, ...);

#pragma mark - 警告日志
/**
 警告日志
 */
FOUNDATION_EXPORT void PTGameWarningLog(NSString *format, ...);

#pragma mark - 错误日志
/**
 错误日志
 */
FOUNDATION_EXPORT void PTGameErrorLog(NSString *format, ...);


/**
 PTTracker分级日志
 
 Debug == YES; 输出全部日志
 
 2.Operation   操作日志 凡用户操作的步骤都能输出
 3.NetworkData 网络数据日志输出
 4.Warning     警告日志
 5.Error       错误日志
 */
#pragma mark - 操作日志
/**
 操作日志
 */
FOUNDATION_EXPORT void PTTrackerOperationLog(NSString *format, ...);

#pragma mark - 网络数据日志
/**
 网络数据日志
 */
FOUNDATION_EXPORT void PTTrackerNetworkDataLog(NSString *format, ...);

#pragma mark - 警告日志
/**
 警告日志
 */
FOUNDATION_EXPORT void PTTrackerWarningLog(NSString *format, ...);

#pragma mark - 错误日志
/**
 错误日志
 */
FOUNDATION_EXPORT void PTTrackerErrorLog(NSString *format, ...);
