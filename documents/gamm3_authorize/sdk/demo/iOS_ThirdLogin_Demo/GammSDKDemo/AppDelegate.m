//
//  AppDelegate.m
//  GammSDKDemo
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

NSString *const YOUR_APPID = @"fdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsffdsf";
NSString *const YOUR_APPKEY = @"fdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfdsfdfdsfdsfds";

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //向SDK注册
    [GammSDKApi registerApp:YOUR_APPID delegate:self];
    return YES;
}

/** SDK注册拦截函数 */
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
    return  [GammSDKApi handleOpenURL:url];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return [GammSDKApi handleOpenURL:url];
}

/** 实现GammSDKApiDelegate协议回调 */
#pragma mark - GammSDKApiDelegate
-(void) onResp:(GammSDKBaseResp*)resp{
    if ([resp isKindOfClass:[GammSDKLoginResp class]]) {
        GammSDKLoginResp *authResp = (GammSDKLoginResp *)resp;
        
        ViewController *rootController = (ViewController *)[(UINavigationController *)[self.window rootViewController] topViewController];
        rootController.code = authResp.code;
        rootController.msg = authResp.msg;
        rootController.state = authResp.state;
        rootController.authCode = authResp.authCode;
        [rootController showOnRespData];
    }
}
@end
