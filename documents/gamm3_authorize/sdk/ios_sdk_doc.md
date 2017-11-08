# iOS巨人账号管家SDK接入文档

## 先决条件

#### 下载并在Xcode中导入静态库 **GammSDK.framework**


## SDK接入流程

#### 1: 导入SDK静态库头文件，然后设置回调代理:

```
#import <UIKit/UIKit.h>

/** 导入SDK静态库 */
#import <GammSDK/GammSDK.h>

/** 设置回调GammSDKApiDelegate代理 */
@interface AppDelegate : UIResponder <UIApplicationDelegate, GammSDKApiDelegate>

@property (strong, nonatomic) UIWindow *window;

@end
```

#### 2: 使用巨人账号管家平台注册的AppID来初始化SDK, 然后在AppDelegate的handleOpenURL方法里添加拦截函数, 同时实现GammSDKApiDelegate回调函数。

```
#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    //向SDK注册
    [GammSDKApi registerApp:@"V040HO2cqqL70j56bZR1" delegate:self];
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
        //处理相关逻辑
    }
}
@end
```

#### 3: 发起登录授权请求

```
/** 点击巨人账号管家App授权 */
- (IBAction)clickAppAuth:(id)sender {
    
    //构造GammSDKLoginReq结构体
    GammSDKLoginReq* req = [[GammSDKLoginReq alloc] init];
    req.state = @"202CB962AC59075B964B07152D234B70";
    
    //第三方向巨人账号管家终端发送一个GammSDKLoginReq消息结构
    BOOL isSuccess = [GammSDKApi sendReq:req viewController:self];
    if (!isSuccess) {
        NSLog(@"请先注册巨人账号管家SDK");
    }
}

```

## SDK接口说明

#### 核心通用接口

```
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
```

## 错误码

状态码         | 描述           |
--------------------|------------------|
0      | 成功   | 
-1     | 普通错误类型  |
-2     | 用户点击取消并返回      |
-3     | 发送失败      |
-4     | 用户拒绝授权或授权失败      |
-5     | 巨人账号管家不支持      |




