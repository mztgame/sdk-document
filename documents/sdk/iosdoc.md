#ios接入：
##游戏尽量使用XCode 6发布游戏，这样方便统一版本，如果必须用XCode 5请提前告知我方

通用库文件：  
Security.framework  
CoreTelephony.framework  
AVFoundation.framework  
Foundation.framework  
UIKit.framework  
CoreGraphics.framework   
CoreLocation.framework  
SystemConfiguration.framework  
libsqlite3.0.dylib  
libsqlite3.dylib  
libz.dylib  
libstdc++.dylib   

通用方法：

* Code Sign Resource Rules Path 请配置为 **$(SDKROOT)/ResourceRules.plist**
* Valid Architectures 请配置为 **armv7 armv7s**
* Other Linker Flags 请配置为 -ObjC
* iOS Deployment Target 请根据游戏需求配置为 6.0 以上
* 为了方便依赖库自动添加，请将Enable Mobules和Link Frameworks Automatically设置为YES

  
配置好以上信息后，一般库会自动导入，如遇到错误请进行以下处理：  
  
* 如果遇到_OBJC_CLASS_$SKPayment、_OBJC_CLASS_$_SKProductsRequest之类的报错，请添加StoreKit.framework  
* 如果遇到_OBJC_CLASS_$_ASIdentifierManger之类的报错，请添加AdSupport.framework  
* 如果遇到_OBJC_CLASS_$_MFMailComposeViewController之类的报错，请添加MessageUI.framework 
* cocos2d的项目，如果遇到_OBJC_CLASS_$_GCControllerConnectionEventHandler之类的报错，请添加GameController.framework  


各个渠道不同：

* XY渠道需要在xcode 6的项目配置里面的Embeded Framework里面添加XYFramework
1、2017.6.6 xy更新所以多加了一个接口，请实现
```
- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [[ZTLibBase getInstance] applicationWillEnterForegroundZTGame:application];
}
```
2、这三个接口里都要实现
```
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url
{
  [[ZTLibBase getInstance] handleOpenURLZTGame:url];
  return YES;
}
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
  [[ZTLibBase getInstance] handleOpenURLZTGame:url];
  return YES;
}
-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options
{
  [[ZTLibBase getInstance] handleOpenURLZTGame:url];
  return YES;
}
```



* 海马渠道需要在xcode 6的项目配置里面的Embeded Framework里面添加AiBeiFramework.framework

* PP助手渠道需要手动添加libMobileGestalt.dylib  

* 爱思渠道  
1、需要手动添加libMobileGestalt.dylib  
2、URL Schemes设置成Asappid。比如：As328（每个项目的appid都写在ztsdk_config.plist配置文件里了）


* 海马玩渠道  
1、会验证Bundle identifier的值，需要设置成商务给的id才能登录。比如：com.mztgame.hm2.hm  
2、URL Schemes设置成ZHPAY-Bundle identifier。比如：ZHPAY-com.mztgame.hm2.hm  
3、需要加入额外库：IOKit.framework

* 同步推渠道  
1、Other Linker Flags 请配置为 -ObjC -lz  
2、URL Schemes设置成Bundle identifier-tb。比如：com.mztgame.hm2.hm-tb

* 49渠道  
1、修改Architectures为$(ARCHS_STANDARD_32_BIT)  
2、URL Schemes设置成com.iOS49AppSdk.游戏名。比如：com.iOS49AppSdk.zhengtu  

* 快用渠道  
1、在配置里面的Embeded Framework里面添加xsdkFramework.framework                                                
2、会验证Bundle identifier的值，需要设置成商务给的id才能登录。比如：com.mztgame.sg.ky    
3、URL identifier设置成：com.ky.xSDK.alipay；URL Schemes设置成Bundle identifier。比如：com.mztgame.dzz.ky 

* 云点渠道  
1、URL Schemes设置成CloudPoint.Bundle identifier。比如：CloudPoint.com.mztgame.hm2.hm 

#游戏需要调用接口：

###UIApplicationDelegate类的接口
***必须保证完全一致，特别是didFinishLaunchingWithOptions函数，要在第一行调用一下单例接口，最后一行调用初始化方法***

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [ZTLibBase instance];
    
      ***游戏window初始化以及makeKeyAndVisible***
    
    
    [[ZTLibBase instance] initZTGameWithID:@"5010" gameName:@"MLGB" delegate:gameListenerDelegate];
    [[ZTLibBase getInstance] viewSetZTViewControl:[self.window rootViewController]];
    return YES;
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    [[ZTLibBase instance] applicationDidEnterBackgroundZTGame];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [[ZTLibBase instance] applicationWillEnterForegroundZTGame];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [[ZTLibBase instance] applicationDidBecomeActiveZTGame];
}

***请注意，此处与之前版本有变动***
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    [[ZTLibBase getInstance] applicationZTGame:application openURL:url sourceApplication:sourceApplication annotation:annotation];
    return YES;
}

```


###功能接口
* **游戏需要根据 是否有用户中心按钮  函数的返回值显示用户中心按钮**  
* **游戏需要根据 是否有切换账号按钮 函数的返回值显示切换账号按钮**  
* **游戏需要根据需要设置不同的区服id，不能全部统一传1**  

```
初始化功能
[[ZTLibBase instance] initZTGameWithID:@"5010" gameName:@"MLGB" delegate:gameListenerDelegate];

登陆功能，参数统一传YES即可
[[ZTLibBase instance] loginZTGame:YES];

**游戏需要根据 是否有用户中心按钮  函数的返回值显示用户中心按钮**  
是否有用户中心按钮
[[ZTLibBase instance]isHasUserCenter]

用户中心功能函数
[[ZTLibBase instance]userCenterZTGame]

**游戏需要根据 是否有切换账号按钮 函数的返回值显示切换账号按钮**  
是否有切换账号按钮
[[ZTLibBase instance]isHasSwitchAccount]

切换账号功能函数
[[ZTLibBase instance]switchAccountZTGame]

**调试日志打印，请在正式版去掉此行代码**  
启用日志打印调试模式
[[ZTLibBase instance]enableDebugMode]

支付功能，参数请在ZTPayInfo的单例中设置
[[ZTLibBase instance]payZTGame]

**游戏需要根据需要设置不同的区服id，不能全部统一传1**  
设置区服务器id
[[ZTLibBase instance]setZoneID:@"1"]

是否已经登录
[[ZTLibBase instance]isLogined]

获取渠道id
[[ZTLibBase instance] getPlatformID]

获取ZTPayInfo单例
[[ZTLibBase instance] getPayInfo]
```

###ZTListenerDelegate回调接口一
* ***请注意所有其他功能接口必须在收到ZTGAME_INIT之后***  
* ***游戏收到ZTGAME_LOGOUT之后要执行登出操作切换到登陆界面，SDK会默认打开登录界面让用户执行登录操作***  
* ***收到ZTGAME_CLOSE通知后要判断用户是否是登陆状态，如果游戏没有登录按钮就要调用登录接口强迫用户登录，如果游戏有登录按钮，可以不处理此通知，等待用户点击登录时判断登录状态来决定是进入游戏还是弹出登录窗口***  

```
- (void)onFinished:(int)what errCode:(int)errCode data:(NSDictionary *)json {
    NSLog(@"onfinished what:%d errorCode:%d json:%@", what, errCode, json);
    switch (what) {
        case ZTGAME_INIT:
            if (errCode == 0) {
                //           call login after init finished
                [[ZTLibBase instance] loginZTGame:YES];
            }
            break;
        case ZTGAME_LOGIN:
            if (errCode == 0) {
                //                game logic after user logged in
                NSLog(@"login json %@", json);
            }
            break;
        case ZTGAME_LOGOUT:
            if (errCode == 0) {
                //                game logic after user logged out
                UIButton *loginBtn = (UIButton *) [self.view viewWithTag:1];
                [loginBtn setEnabled:YES];
            }
            break;
        case ZTGAME_CLOSE:
            if (errCode == 0) {
                //                when user close sdk window,check user is logged in or not,if user isn't logged in,then reopen the login window
                if (![[ZTLibBase instance] isLogined]) {
                    [[ZTLibBase instance] loginZTGame:NO];
                }
            }
        case ZTGAME_PAY:
            if (errCode == 0) {
                //                pay finished success
            }
            else {
                //                pay finished fail
            }
        default:break;
    }
}
```

###ZTListenerDelegate回调接口二
* ***请注意在该函数里处理页面绘制的触发和停止***  

```
- (void)switchAccountView:(int)what
{
    switch (what) {
        case ZTGAME_VIEWSHOW:

            
            break;
        case ZTGAME_VIEWCLOSE:

            
            break;
        default:break;
    }
    
}

```

###Login返回Json格式

device_type：设备类型  
pt_id: 平台id  
token：登陆验证token  
accid：用户uid（**现在为数字格式，游戏需要支持字符串格式**）  
imei：用户手机imei串  
action：操作字符串  
account：用户名（统一返回为“默认账户”）  
mac：mac地址  
pt_id：渠道号  
ip：用户ip地址 

```
{accid = 461902;  account = "默认账户"";  action = login;  "device_type" = "x86_64";  imei = "87835508-6849-4805-ADB9-B4780A2E6E1D";  ip = "192.168.1.109";  mac = ""; "pt_id" = 2;  token = d9e3057af0f7fcfe;} 
```

###ZTPayInfo参数信息
NSString *appOrderId;  // **无需游戏方设置，保留参数**  
NSString *productId;   // **商品id，仅苹果官方使用**  
NSString *productName; // **商品名称**  
int productPrice;      // **商品价格，请注意货币单位是人民币分**  
int count;             // **商品数量，必须设置为1**  
int exchangeRate;      // **虚拟货币汇率，单位为1元对应多少游戏币**  
NSString *extra;       // **扩展信息，游戏方可以设置的透传参数，会回传给游戏服务器端**

  
###push推送功能：  
苹果push推送：  
请实现：  
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {

    [ZTServicePush registerDeviceToken:deviceToken];
    
}  

如果想连调版本测试，请在配置文件中配置pushDebug  
状态为1为连调测试，0为发布版本，默认为发布版本

###一键加群功能：  
一键加群：  
请实现：  
if([[ZTLibBase getInstance] isHasQQGroup])  
                {  
                    [[ZTLibBase getInstance] joinQQGroup];  
                }  
                
###提交玩家最后登录游戏区：  
登录后，调用： 
[[ZTLibBase getInstance] updateLastGameZone:zoneId block:^(BOOL status) {

}];

###获取玩家最后登录游戏区：
登录后，调用： 
[[ZTLibBase getInstance] loadLastGameZoneBlock:^(BOOL status, NSString *zoneId) {

}];

QQ号请提交我们，我们会后台配置，便于后期管理  

Xcode7以上适配iOS9要在 info.plist加上 LSApplicationQueriesSchemes 类型 Array,在LSApplicationQueriesSchemes下添加item类型String,值设为mqqapi

> 另外：在Xcode7则需在info.plist配置以下项
> 在Info.plist中添加NSAppTransportSecurity类型Dictionary，在NSAppTransportSecurity下添加NSAllowsArbitraryLoads类型Boolean,值设为YES
> 在Build Settings下的 Build Options-> Enable Bitcode 项设置值为No

###备注
渠道id以及游戏id可以统一从此wiki链接查询
[http://wiki.mztgame.com/index.php/%E6%B8%A0%E9%81%93%E4%BF%A1%E6%81%AF%E5%88%97%E8%A1%A8](http://wiki.mztgame.com/index.php/%E6%B8%A0%E9%81%93%E4%BF%A1%E6%81%AF%E5%88%97%E8%A1%A8)
