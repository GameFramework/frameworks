//
//  ProtovollUserView.h
//  RSDKFramework
//
//  Created by 邹明明 on 17/3/6.
//  Copyright © 2017年 rsdk. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ProtovollUserView : UIViewController
+(ProtovollUserView*)shareProtocolUserView;
-(void)creatUserview:(NSString*)customParams;

@end


@interface ProtovollUserCell : UITableViewCell

@end