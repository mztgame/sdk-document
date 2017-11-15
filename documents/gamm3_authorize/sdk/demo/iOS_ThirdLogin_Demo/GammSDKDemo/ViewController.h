//
//  ViewController.h
//  GammSDKDemo
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITextView *infoTextView;
@property (assign, nonatomic)  NSInteger code; //错误码
@property (nonatomic)  NSString *msg; //错误消息
@property (nonatomic)  NSString *state; //回传state
@property (nonatomic)  NSString *authCode; //OAuth授权码

/** 显示数据 */
- (void)showOnRespData;
@end

