//
//  ViewController.m
//  GammSDKDemo
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import "ViewController.h"
#import <GammSDK/GammSDK.h>
#import "AFNetworking.h"
#import "SVProgressHUD.h"
#import "is.h"
#import "common.h"
#import "AppDelegate.h"

static NSString *const URLHost = @"http://gamm3.dev.ztgame.com"; //Dev
//static NSString *const URLHost = @"https://gamm3.ztgame.com"; //Pro

@interface NSDictionary (Unicode)
- (NSString*)my_description;
@end

@interface ViewController ()
@property (strong, nonatomic) NSDictionary *accessTokenDic; //获取accessToken字典
@property (strong, nonatomic) NSDictionary *refreshAccessTokenDic; //刷新accessToken字典
@property (strong, nonatomic) NSDictionary *userInfoDic; //获取用户信息
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [GammSDKApi setGammDebug:YES];
    [SVProgressHUD setDefaultStyle:SVProgressHUDStyleDark];
}

/** 显示数据 */
- (void)showOnRespData{
     //获取授权结果
    NSMutableString *infoString = [[NSMutableString alloc] initWithString:@"****** Auth授权结果 ******\n"];
    [infoString appendFormat:@"code: %ld\n", (long)_code];
    [infoString appendFormat:@"msg: %@\n", _msg];
    [infoString appendFormat:@"state: %@\n", _state];
    [infoString appendFormat:@"authCode: %@\n", _authCode];
    
    //获取accessToken
    if (_accessTokenDic && [_accessTokenDic count]) {
        [infoString appendFormat:@"\n\n ****** 获取access_token ******\n"];
        [infoString appendFormat:@"access_token: %@\n", _accessTokenDic[@"access_token"]];
        [infoString appendFormat:@"expires_in: %@\n", _accessTokenDic[@"expires_in"]];
        [infoString appendFormat:@"refresh_token: %@\n", _accessTokenDic[@"refresh_token"]];
        [infoString appendFormat:@"expires_in_refresh: %@\n", _accessTokenDic[@"expires_in_refresh"]];
        [infoString appendFormat:@"openid: %@\n", _accessTokenDic[@"openid"]];
        
    }
    
    //刷新accessToken
    if (_refreshAccessTokenDic && [_refreshAccessTokenDic count]) {
        [infoString appendFormat:@"\n\n ****** 刷新access_token ******\n"];
        [infoString appendFormat:@"access_token: %@\n", _refreshAccessTokenDic[@"access_token"]];
        [infoString appendFormat:@"expires_in: %@\n", _refreshAccessTokenDic[@"expires_in"]];
        [infoString appendFormat:@"refresh_token: %@\n", _refreshAccessTokenDic[@"refresh_token"]];
        [infoString appendFormat:@"expires_in_refresh: %@\n", _refreshAccessTokenDic[@"expires_in_refresh"]];
        [infoString appendFormat:@"openid: %@\n", _refreshAccessTokenDic[@"openid"]];
        
    }
    
    //获取用户信息
    if (_userInfoDic && [_userInfoDic count]) {
        [infoString appendFormat:@"\n\n ****** 获取用户信息 ******\n"];
        [infoString appendFormat:@"account: %@\n", _userInfoDic[@"account"]];
        [infoString appendFormat:@"nickname: %@\n", _userInfoDic[@"nickname"]];
        [infoString appendFormat:@"sex: %@\n", _userInfoDic[@"sex"]];
        [infoString appendFormat:@"birth: %@\n", _userInfoDic[@"birth"]];
    }
    
    _infoTextView.text = infoString;
}

#pragma mark - 事件点击
/** 点击巨人账号管家App授权 */
- (IBAction)clickAppAuth:(id)sender {
    
    //构造GammSDKLoginReq结构体
    GammSDKLoginReq* req = [[GammSDKLoginReq alloc] init];
    //随机生成的标识符
    req.state = @"202CB962AC59075B964B07152D234B70";
    
    //第三方向巨人账号管家终端发送一个GammSDKLoginReq消息结构
    BOOL isSuccess = [GammSDKApi sendReq:req viewController:self];
    if (!isSuccess) {
        NSLog(@"请先注册巨人账号管家SDK,或是没有安装巨人账号管家App");
    }else{
        self.accessTokenDic = nil;
        self.refreshAccessTokenDic = nil;
        self.userInfoDic = nil;
    }
}

/** 点击获取access_token */
- (IBAction)clickGetAccessToken:(id)sender {
    [self requestForGetAccessToken];
}

/** 点击获取用户信息 */
- (IBAction)clickGetUserInfo:(id)sender {
    [self requestForGetUserInfo];
}

/** 点击刷新access_token */
- (IBAction)clickRefreshAccessToken:(id)sender {
    [self requestForRefreshAccessToken];
}

#pragma mark - 网络请求
/** 通过code获取access_token */
- (void)requestForGetAccessToken{
    
    if (isEmptyString(_authCode)) {
        [SVProgressHUD showErrorWithStatus:@"请先点击授权获取授权码code"];
        return;
    }
    
    NSString *sign = [self MD5SignApiParameters:@{@"app_id": YOUR_APPID,
                                                  @"code": _authCode
                                                  }];
    NSString *URL = [NSString stringWithFormat:@"%@/sns/oauth2/access_token?app_id=%@&code=%@&sign=%@",
                     URLHost, YOUR_APPID, _authCode, sign];
    
    [SVProgressHUD show];
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    NSLog(@"%s = %@", __PRETTY_FUNCTION__, URL);
    [manager GET:URL parameters:nil progress:^(NSProgress * _Nonnull downloadProgress) {
        
    }success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        [SVProgressHUD dismiss];
        NSLog(@"%s = %@", __PRETTY_FUNCTION__, responseObject);
        [self showAlertView:[responseObject my_description]];
        
        self.accessTokenDic = responseObject[@"data"];
        [self showOnRespData];
        
    }failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull   error) {
        [SVProgressHUD dismiss];
        [self showAlertView:[error localizedDescription]];
    }];
}

/** 点击刷新access_token */
- (void)requestForRefreshAccessToken{
    
    if (isEmptyString(_authCode)) {
        [SVProgressHUD showErrorWithStatus:@"请先点击授权获取授权码code"];
        return;
    }
    
    NSString *sign = [self MD5SignApiParameters:@{@"app_id": YOUR_APPID,
                                                  @"refresh_token": _accessTokenDic[@"refresh_token"],
                                                  }];
    NSString *URL = [NSString stringWithFormat:@"%@/sns/oauth2/new-access_token?app_id=%@&refresh_token=%@&sign=%@",
                     URLHost, YOUR_APPID, _accessTokenDic[@"refresh_token"], sign];
    
    [SVProgressHUD show];
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    NSLog(@"%s = %@", __PRETTY_FUNCTION__, URL);
    [manager GET:URL parameters:nil progress:^(NSProgress * _Nonnull downloadProgress) {
        
    }success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        [SVProgressHUD dismiss];
        NSLog(@"%s = %@", __PRETTY_FUNCTION__, responseObject);
        [self showAlertView:[responseObject my_description]];
        
        self.refreshAccessTokenDic = responseObject[@"data"];
        [self showOnRespData];
        
    }failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull   error) {
        [SVProgressHUD dismiss];
        [self showAlertView:[error localizedDescription]];
    }];
}

/** 获取用户信息 */
- (void)requestForGetUserInfo{
    
    if (isEmptyString(_authCode)) {
        [SVProgressHUD showErrorWithStatus:@"请先点击授权获取授权码code"];
        return;
    }
    
    NSString *sign = [self MD5SignApiParameters:@{@"access_token": _accessTokenDic[@"access_token"],
                                                  @"openid": _accessTokenDic[@"openid"],
                                                  }];
    NSString *URL = [NSString stringWithFormat:@"%@/sns/account/userinfo?access_token=%@&openid=%@&sign=%@",
                     URLHost, _accessTokenDic[@"access_token"], _accessTokenDic[@"openid"], sign];
    
    [SVProgressHUD show];
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    NSLog(@"%s = %@", __PRETTY_FUNCTION__, URL);
    [manager GET:URL parameters:nil progress:^(NSProgress * _Nonnull downloadProgress) {
        
    }success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        [SVProgressHUD dismiss];
        NSLog(@"%s = %@", __PRETTY_FUNCTION__, responseObject);
        [self showAlertView:[responseObject my_description]];
        
        self.userInfoDic = responseObject[@"data"];
        [self showOnRespData];
        
    }failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull   error) {
        [SVProgressHUD dismiss];
        [self showAlertView:[error localizedDescription]];
    }];
}

#pragma mark - 网络加密算法
/** 账号管家签名算法
 1.将所有需要的参数(还没有sign参数)数组按照 Asics码倒序排列。
 2.将倒序后的数组拼接成http的query串
 3.执行一次md5，得到一个md5串
 4.将第一次得到的md5串，拼接上app_key
 5.再次md5，得到签名 sign。
 */
- (NSString *)MD5SignApiParameters:(NSDictionary *)requestParams{
    NSMutableDictionary *parameters = [requestParams mutableCopy];
    
    //1.
    NSArray *keys = [parameters allKeys];
    NSArray *sortedKeys = [keys sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        return [obj2 compare:obj1 options:NSNumericSearch];
    }];
    NSLog(@"1. 倒序排序参数 ====== %@", sortedKeys);
    
    //2.
    NSMutableString *package = [NSMutableString string];
    for (NSInteger i=0; i<[sortedKeys count]; i++) {
        NSString *key = [sortedKeys objectAtIndex:i];
        [package appendString:key];
        [package appendString:@"="];
        [package appendString:[parameters objectForKey:key]];
        
        if (i != ([sortedKeys count] -1)) {
            [package appendString:@"&"];
        }
    }
    NSLog(@"2. 倒序查询字符串 ====== %@", package);
    
    //3.
    NSString *md5Package = md5(package);
    NSLog(@"3. 查询字符串md5后是 ====== %@", md5Package);
    
    //4.
    NSString *signStr = [NSString stringWithFormat:@"%@&app_key=%@", md5Package, YOUR_APPKEY];
    NSLog(@"4. 拼接上app_key后得到 ====== %@", signStr);
    
    //5.
    NSString *md5Sign = md5(signStr);
    NSLog(@"5. 签名sign ====== %@", md5Sign);
    
    return md5Sign;
}

#pragma mark - 弹框
- (void)showAlertView:(NSString *)msg{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"返回结果"
                                                        message:msg
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
    [alertView show];
}
@end

#pragma mark - NSDictionary 扩展
@implementation NSDictionary (Unicode)
- (NSString*)my_description {
    NSString *desc = [self description];
    desc = [NSString stringWithCString:[desc cStringUsingEncoding:NSUTF8StringEncoding] encoding:NSNonLossyASCIIStringEncoding];
    return desc;
}
@end
