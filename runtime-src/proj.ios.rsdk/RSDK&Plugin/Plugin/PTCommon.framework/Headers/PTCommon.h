//
//  PTCommon.h
//  PTCommon
//
//  Created by 曹恩康 on 2016/12/19.
//  Copyright © 2016年 曹恩康. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for PTCommon.
FOUNDATION_EXPORT double PTCommonVersionNumber;

//! Project version string for PTCommon.
FOUNDATION_EXPORT const unsigned char PTCommonVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <PTCommon/PublicHeader.h>

#pragma mark - Platform
/* platform */
#import <PTCommon/PTCommonPlatform.h>

#pragma mark - Data
/* dataUtil */
#import <PTCommon/PTDataUtil.h>
/* model */
#import <PTCommon/PTFBShareVO.h>
#import <PTCommon/PTGameInfoVO.h>
#import <PTCommon/PTPayInfo.h>
#import <PTCommon/PTProductVO.h>
#import <PTCommon/PTShareVO.h>
#import <PTCommon/PTTransactionVO.h>
#import <PTCommon/PTUserInfo.h>
#import <PTCommon/PTUserVO.h>
#import <PTCommon/PTVKShareVO.h>

#pragma mark - Tools
/* headers *//*
#import <PTCommon/PTErrorGetFormServe.h>
#import <PTCommon/PTGlobal.h>
#import <PTCommon/PTUrlDefine.h>*/
/* gameTextField */
#import <PTCommon/PTGameTextField.h>
/* normalUtils */
#import <PTCommon/PTNormalUtils.h>
/* uiUtils */
#import <PTCommon/PTUIUtils.h>
/* loadingView */
#import <PTCommon/PTLoadingView.h>
/* PTLog */
#import <PTCommon/PTLog.h>

#pragma mark - Dependence
/* UIViewController+CWPopup */
#import <PTCommon/UIViewController+CWPopup.h>

#pragma mark - Network
/* PTGameClient */
/**
 隐藏PTGameClient类，直接调用PTCommonPlatform的‘用户部分相关接口’
 
 #import <PTCommon/PTGameClient.h>
 */

#pragma mark - Interface
/* PTCountUtils */
#import <PTCommon/PTCountUtils.h>
