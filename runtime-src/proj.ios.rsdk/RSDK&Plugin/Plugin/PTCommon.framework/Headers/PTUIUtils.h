//
//  PTUIUtils.h
//  PTCommon
//
//  Created by 杨建亚 on 14-4-25.
//  Copyright (c) 2014年 Dwarven. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class PTGameTextField;

@interface PTUIUtils : NSObject

+ (float)getPositionScaleX;

+ (float)getPositionScaleY;

// 原CPUtils
+ (CGSize)getStringSize:(NSString *)string
               withFont:(UIFont *)font
      withconstrainSize:(CGSize)constraintSize;

// 原UIUtils
+ (CGSize)getStringSizeForUI:(NSString*)str
                        font:(UIFont*)font;

+ (CGFloat)heightForString:(NSString*)str
                     width:(CGFloat)width
                      font:(UIFont*)font;

+ (UILabel *)createLabelForText:(NSString*)text
                           font:(UIFont *)font
                        offsetX:(float)offsetX
                        offsetY:(float)offsetY;

+ (UIImage *)imageWithName:(NSString *)name
                      type:(NSString *)type;

+ (UIWebView *)webViewForLoadGif:(NSString *)name
                            type:(NSString *)type;

+ (UIButton *)createButton:(CGRect )rect
                    target:(id)target
                    action:(SEL)action
           normalImageName:(NSString *)normalImageName
      highlightedImageName:(NSString *)highlightedImageName
         selectedImageName:(NSString *)selectedImageName
                     title:(NSString *)title;

+ (PTGameTextField *)createTextField:(CGRect)rect
                           delegate:(id)delegate
                         valignment:(UIControlContentVerticalAlignment)valignment
                    backgroundImage:(UIImage *)backgroundImage
                    backgroundColor:(UIColor *)backgroundColor
                        borderStyle:(UITextBorderStyle)borderStyle
                    clearButtonMode:(UITextFieldViewMode)clearButtonMode
                            enabled:(BOOL)enabled font:(UIFont *)font
                       keyboardType:(UIKeyboardType)keyboardType
                        placeholder:(NSString *)placeholder
                                tag:(int)tag
                      textAlignment:(NSTextAlignment)textAlignment
                          textColor:(UIColor *)textColor;

+ (void)setViewBoder:(UIView *)view
              circle:(BOOL)circle
              border:(BOOL)border
              shadow:(BOOL)shadow;

+ (UIColor *)colorForHex:(NSString *)hexColor;

@end
