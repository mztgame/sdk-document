//
//  GammSDKApi.h
//  GammSDK
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GammSDKApiObject.h"

#pragma mark - GammSDKApiDelegate
/*! @brief 接收并处理来自巨人账号管家终端程序的事件消息
 *
 * 接收并处理来自巨人账号管家终端程序的事件消息，期间巨人账号管家界面会切换到第三方应用程序。
 * GammSDKApiDelegate 会在handleOpenURL:delegate:中使用并触发。
 */
@protocol GammSDKApiDelegate <NSObject>
@optional

/**
 收到一个来自巨人账号管家的请求，异步处理完成后必须调用sendResp发送处理结果给巨人账号管家。
 
 @param req 具体请求内容，是自动释放的
 */
-(void)onReq:(GammSDKBaseReq*)req;

/**
 发送一个sendReq后，收到巨人账号管家的回应onResp。
 
 @param resp 具体的回应内容，是自动释放的
 */
-(void)onResp:(GammSDKBaseResp*)resp;

@end

@interface GammSDKApi : NSObject

/**
 向巨人账号管家终端程序注册第三方应用。
 
 @param appid 在巨人平台开发者注册的AppID
 @param delegate 巨人账号管家启动第三方应用时传递过来的URL
 @return 成功返回YES，失败返回NO。
 */
+(BOOL)registerApp:(NSString *)appid delegate:(id<GammSDKApiDelegate>) delegate;

/**
 设置sdk是否是debug状态
 
 @param isDebug YES:打开Debug模式，NO:关闭Debug模式
 */
+ (void)setGammDebug:(BOOL)isDebug;

/**
 判断巨人账号管家是否安装
 
 @return 已安装返回YES，未安装返回NO。
 */
+ (BOOL)isGammInstalled;

/**
 是否是Debug模式
 
 @return YES：是Debug模式，NO：不是
 */
+ (BOOL)isDebug;

/**
 SDK的版本号
 
 @return 版本号
 */
+ (NSString *)gammVersion;

/**
 处理巨人账号管家通过URL启动App时传递的数据
 
 @param url 需要在 application:openURL:sourceApplication:annotation:或者application:handleOpenURL中调用。
 @return GammSDKApiDelegate对象，用来接收巨人账号管家触发的消息。
 */
+(BOOL)handleOpenURL:(NSURL *) url;

/**
 发送请求到巨人账号管家，等待巨人账号管家返回onResp
 函数调用后，会切换到巨人账号管家的界面。第三方应用程序等待巨人账号管家返回onResp。巨人账号管家在异步处理完成后一定会调用onResp。
 
 @param req 具体的发送请求，在调用函数后，请自己释放。
 @param viewController 当前界面对象。
 @return 成功返回YES，失败返回NO。（一般返回失败NO，需要先调用方法registerApp:delegate:进行注册）
 */
+ (BOOL)sendReq:(GammSDKBaseReq*)req viewController:(UIViewController*)viewController;

@end

