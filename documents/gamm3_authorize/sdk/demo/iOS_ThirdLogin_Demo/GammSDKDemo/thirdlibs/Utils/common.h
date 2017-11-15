//
//  common.h
//  GiantAssistant
//
//  Created by robin on 2017/9/26.
//  Copyright © 2017年 Giant. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/** 检测字符串如果为Null，就设置为空字符串 */
NSString* defaultEmptyString(id object);
NSArray*  defaultEmptyArray(id object);

/** 转字符串 */
NSString* stringWithInt(NSInteger num);
NSString* stringWithFloat(CGFloat num);

/** MD5字符串 */
NSString* md5(NSString* input);

/** 验证 */
BOOL validateEmail(NSString* email);
BOOL validateUserName(NSString* name);
BOOL validateMobile(NSString* mobile);
BOOL validatePhoneNumber(NSString* phoneNum);
BOOL validateIdentityCard(NSString *identityCard);
BOOL validateNumber(NSString *str);
BOOL validateDecimal(NSString *str);
BOOL validatePassword(NSString* passWord);
BOOL validateQQ(NSString *str);
BOOL validateWeixin(NSString* str);
BOOL validateAuthCode(NSString *str);

/**
 输入设计图的宽高（设计图是iPhone6尺寸）
 根据屏幕宽高计算真实的宽高
 */
CGFloat realSizeWidth(CGFloat width);
CGFloat realSizeHeight(CGFloat height);

/** 删除UserDefault所有数据 */
void removeAllUserDefault();

/** 解析URL获取参数 */
NSMutableDictionary *parseURL(NSURL *URL);
/** 解析URL获取查询参数 */
NSMutableDictionary *parseURLQueryParams(NSURL *URL);

/** 获取焦点window */
UIWindow *frontWindow();

/** 在主线程运行 */
void dispatch_main_async_safe(void (^block)(void));

/** 手机号18618138919转换成186****8919 */
NSString* convertHidePhone(NSString *phoneNumber);

NSString* getDocumentsFilePath(const NSString* fileName);
NSString* getResourcePath(NSString* basePath, NSString* resName, NSString* resType);
NSURL* getResourceUrl(NSString* basePath, NSString* resName, NSString* resType);
