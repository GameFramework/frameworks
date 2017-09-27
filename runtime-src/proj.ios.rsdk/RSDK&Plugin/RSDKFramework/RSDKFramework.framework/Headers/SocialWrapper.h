//
//  SocialWrapper.h
//  PluginProtocol
//
//  Created by cocos2dx on 14-10-9.
//  Copyright (c) 2014年 cocos2dx. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum : NSUInteger {
    // code for leaderboard feature
    kScoreSubmitSucceed =1,/**< enum value is callback of succeeding in submiting. */
    kScoreSubmitfail,/**< enum value is callback of failing to submit . */
    
    // code for achievement feature
    kAchUnlockSucceed,/**< enum value is callback of succeeding in unlocking. */
    kAchUnlockFail,/**< enum value is callback of failing to  unlock. */
    
    kSocialSignInSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignInFail,/**< enum value is callback of failing to  login. */
    
    kSocialSignOutSucceed,/**< enum value is callback of succeeding to login. */
    kSocialSignOutFail,/**< enum value is callback of failing to  login. */
    
    kSocialGetMyInfoSucceed,
    kSocialGetMyInfoFailed,
    
    kSocialGetFriendSucceed,
    kSocialGetFriendFailed,
    
    kSocialInviteSucceed,
    kSocialInviteFailed,
    kSocialInviteCanceled,
    kSocialInviteRefuse,
    
    kSocialDeepLinkData,
} SocialActionRetCode;

typedef enum : NSUInteger{
    PlayerScopeGlobal = 0,
    PlayerScopeFriendsOnly = 0
} PlayerScope;
    
typedef enum : NSUInteger{
    TimeScopeToday = 0,
    TimeScopeWeek,
    TimeScopeAllTime
} TimeScope;

@interface SocialWrapper : NSObject

/*!
 * @abstract 分享社交回调方法.
 */
+ (void) onSocialResult:(id)pPlugin retCode:(int)ret retMsg:(NSString*)msg;

@end
