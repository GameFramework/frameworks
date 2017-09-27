//
//  PTGameTextField.h
//  PTCommon
//
//  Created by 曹恩康 on 2016/12/19.
//  Copyright © 2016年 曹恩康. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface PTGameTextField : UITextField

@property (nonatomic, strong) NSString    *imageName;
@property (nonatomic, strong) UIImageView *imageView;
@property (nonatomic, strong) UIImageView *tipImageView;
@property (nonatomic, strong) UIButton    *clearBtn;

@end
