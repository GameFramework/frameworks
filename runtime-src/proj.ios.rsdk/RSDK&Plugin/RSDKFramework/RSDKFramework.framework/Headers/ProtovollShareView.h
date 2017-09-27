//
//  ProtovollUserView.h
//  RSDKFramework
//
//  Created by 邹明明 on 17/3/6.
//  Copyright © 2017年 rsdk. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ProtovollShareView : UIViewController
+(ProtovollShareView*)shareProtovollShareView;
-(void)creatShareview:(NSMutableDictionary*)shareInfo;

@end


@interface ProtovollShareCell : UITableViewCell

@end