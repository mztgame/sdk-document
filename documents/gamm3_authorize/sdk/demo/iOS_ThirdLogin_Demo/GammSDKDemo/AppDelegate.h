//
//  AppDelegate.h
//  GammSDKDemo
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import <UIKit/UIKit.h>

UIKIT_EXTERN NSString *const YOUR_APPID;
UIKIT_EXTERN NSString *const YOUR_APPKEY;

/** 导入SDK静态库 */
#import <GammSDK/GammSDK.h>

/** 设置回调GammSDKApiDelegate代理 */
@interface AppDelegate : UIResponder <UIApplicationDelegate, GammSDKApiDelegate>

@property (strong, nonatomic) UIWindow *window;

@end

