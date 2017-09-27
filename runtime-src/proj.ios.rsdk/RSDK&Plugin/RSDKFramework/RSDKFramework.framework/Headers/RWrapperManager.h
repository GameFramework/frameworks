//
//  RWrapperManager.h
//  RSDKFramework
//
//  Created by 邹明明 on 16/12/20.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RWrapperManager : NSObject<UIApplicationDelegate>

+ (RWrapperManager*)sharedInstance;
- (instancetype)init;
@end
