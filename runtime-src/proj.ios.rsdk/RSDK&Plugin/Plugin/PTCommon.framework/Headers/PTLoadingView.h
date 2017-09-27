//
//  PTLoadingView.h
//  PTCommon
//
//  Created by 杨建亚 on 14-4-22.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void (^LoadingBlock)();

@interface PTLoadingView : UIView

@property(nonatomic) BOOL switchAccountFlag;

/* 显示 */
- (void)showInView:(UIView *)view withMessage:(NSString *)msg;

/* 移除 */
- (void)removeSelfFromSuperView:(id)sender;

- (void)setLoadingBlock:(LoadingBlock)loadingBlock;

@end
