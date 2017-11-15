//
//  common.m
//  GiantAssistant
//
//  Created by robin on 2017/9/26.
//  Copyright © 2017年 Giant. All rights reserved.
//
#import <CommonCrypto/CommonDigest.h>
#import "NSString+URLEncode.h"
#import "common.h"
#import "is.h"

NSString* defaultEmptyString(id object) {
    
    if (isNull(object)) {
        return @"";
    }
    
    if ([object isKindOfClass:[NSString class]]) {
        return object;
    }
    
    if ([object respondsToSelector:@selector(stringValue)]) {
        return [object stringValue];
    }
    
    return @"";
}

NSArray*  defaultEmptyArray(id object){
    if (isNull(object)) {
        return [NSArray array];
    }
    
    if ([object isKindOfClass:[NSArray class]]) {
        return object;
    }
    
    return [NSArray array];
}

NSString* stringWithInt(NSInteger num)
{
    return [NSString stringWithFormat:@"%ld",(long)num];
}
NSString* stringWithFloat(CGFloat num)
{
    return [NSString stringWithFormat:@"%f",num];
}

NSString* md5(NSString* input){
    const char *cStr = [input UTF8String];
    unsigned char digest[CC_MD5_DIGEST_LENGTH];
    
    CC_MD5(cStr, (CC_LONG)strlen(cStr), digest);
    
    NSMutableString *result = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for (int i = 0; i < CC_MD5_DIGEST_LENGTH; i++) {
        [result appendFormat:@"%02X", digest[i]];
    }
    
    return [result lowercaseString];
}

//邮箱
BOOL validateEmail(NSString* email) {
    NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
    return [emailTest evaluateWithObject:email];
}

//用户名
/*
 1、一个正则表达式，只含有汉字、数字、字母、下划线不能以下划线开头和结尾：
 
 ^(?!_)(?!.*?_$)[a-zA-Z0-9_\u4e00-\u9fa5]+$  其中：
 ^  与字符串开始的地方匹配
 (?!_)　　不能以_开头
 (?!.*?_$)　　不能以_结尾
 [a-zA-Z0-9_\u4e00-\u9fa5]+　　至少一个汉字、数字、字母、下划线
 $　　与字符串结束的地方匹配
 
 放在程序里前面加@，否则需要\\进行转义 @"^(?!_)(?!.*?_$)[a-zA-Z0-9_\u4e00-\u9fa5]+$"
 （或者：@"^(?!_)\w*(?<!_)$"    或者  @" ^[\u4E00-\u9FA50-9a-zA-Z_]+$ "  )
 
 2、只含有汉字、数字、字母、下划线，下划线位置不限：
 ^[a-zA-Z0-9_\u4e00-\u9fa5]+$
 
 3、由数字、26个英文字母或者下划线组成的字符串
 ^\w+$
 
 4、2~4个汉字
 @"^[\u4E00-\u9FA5]{2,4}$";
 
 5、
 ^[\w-]+(\.[\w-]+)*@[\w-]+(\.[\w-]+)+$
 
 用：(Abc)+    来分析：  XYZAbcAbcAbcXYZAbcAb
 */
BOOL validateUserName(NSString* name) {
    NSString *nameRegex = @"^[A-Za-z0-9\u4e00-\u9fa5-_\\.]+$";
    
    NSPredicate *nameTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", nameRegex];
    return [nameTest evaluateWithObject:name];
}

//密码
BOOL validatePassword(NSString* passWord)
{
    NSString *passWordRegex = @"^[a-zA-Z0-9]{6,12}+$";
    NSPredicate *passWordPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",passWordRegex];
    return [passWordPredicate evaluateWithObject:passWord];
}

//手机
BOOL validateMobile(NSString* mobile) {
    NSString *phoneRegex = @"^(1[1-9])\\d{9}$";
    NSPredicate *phoneTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",phoneRegex];
    return [phoneTest evaluateWithObject:mobile];
}

//身份证
BOOL validateIdentityCard(NSString *identityCard){
    BOOL flag;
    if (identityCard.length <= 0) {
        flag = NO;
        return flag;
    }
    NSString *regex2 = @"^(\\d{14}|\\d{17})(\\d|[xX])$";
    NSPredicate *identityCardPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex2];
    return [identityCardPredicate evaluateWithObject:identityCard];
}

//电话
BOOL validatePhoneNumber(NSString* phoneNum) {
    NSString *phoneRegex = @"((\\d{11})|^((\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1})|(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1}))$)";
    NSPredicate *phoneTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",phoneRegex];
    return [phoneTest evaluateWithObject:phoneNum];
}

BOOL validateNumber(NSString *str){
    NSString *regex = @"^[0-9-]*$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
    return [predicate evaluateWithObject:str];
}

BOOL validateDecimal(NSString *str){
    NSString *regex = @"^-?(0|\\d+)(\\.\\d+)?$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
    return [predicate evaluateWithObject:str];
}

//检查QQ号码
BOOL validateQQ(NSString *str) {
    NSString *regex = @"^[1-9][0-9]{4,}$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
    return [predicate evaluateWithObject:str];
}

//检查验证码
BOOL validateAuthCode(NSString *str) {
    NSString *regex = @"^[a-zA-Z0-9]{4,12}+$";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
    return [predicate evaluateWithObject:str];
}

//微信验证
BOOL validateWeixin(NSString* str)
{
    NSString *weixinRegex = @"^[a-zA-Z0-9]{4,}+$";
    NSPredicate *weixinPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",weixinRegex];
    return [weixinPredicate evaluateWithObject:str];
}

void removeAllUserDefault(){
    NSString *bundle = [[NSBundle mainBundle] bundleIdentifier];
    [[NSUserDefaults standardUserDefaults] removePersistentDomainForName:bundle];
}

NSMutableDictionary *parseURL(NSURL *URL){
    NSString *queryParams = URL.query;
    NSMutableDictionary *params = [NSMutableDictionary new];
    for (NSString *param in [queryParams componentsSeparatedByString:@"&"]) {
        NSArray *parts = [param componentsSeparatedByString:@"="];
        if([parts count] < 2) continue;
        [params setObject:[[parts objectAtIndex:1] URLDecode] forKey:[[parts objectAtIndex:0] URLDecode]];
    }
    
    [params setObject:defaultEmptyString(URL.scheme) forKey:@"scheme"];
    [params setObject:defaultEmptyString(URL.host) forKey:@"host"];
    [params setObject:defaultEmptyString(URL.path) forKey:@"path"];
    [params setObject:defaultEmptyString(queryParams) forKey:@"query"];
    
    return params;
}

NSMutableDictionary *parseURLQueryParams(NSURL *URL){
    NSString *queryParams = URL.query;
    NSMutableDictionary *params = [NSMutableDictionary new];
    for (NSString *param in [queryParams componentsSeparatedByString:@"&"]) {
        NSArray *parts = [param componentsSeparatedByString:@"="];
        if([parts count] < 2) continue;
        [params setObject:[[parts objectAtIndex:1] URLDecode] forKey:[[parts objectAtIndex:0] URLDecode]];
    }
    return params;
}


void dispatch_main_async_safe(void (^block)(void)){
    if (strcmp(dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL), dispatch_queue_get_label(dispatch_get_main_queue())) == 0) {
        block();
    } else {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}

NSString* convertHidePhone(NSString *phoneNumber){
    if(phoneNumber.length >= 7){
        NSString *hidePhoneNumber = [NSString stringWithFormat:@"%@****%@",[phoneNumber substringWithRange:NSMakeRange(0,3)],[phoneNumber substringWithRange:NSMakeRange(phoneNumber.length-4,4)]];
        return hidePhoneNumber;
    }else{
        return phoneNumber;
    }
}

NSString* getDocumentsFilePath(const NSString* fileName) {
    NSString* documentRoot = [NSHomeDirectory() stringByAppendingPathComponent:@"/Documents"];
    return [documentRoot stringByAppendingPathComponent:[NSString stringWithFormat:@"/%@", fileName]];
}


NSString* getResourcePath(NSString* basePath, NSString* resName, NSString* resType) {
    NSString* path = [NSString pathWithComponents:[NSArray arrayWithObjects:basePath, resName, nil]];
    return [[NSBundle mainBundle] pathForResource:path ofType:resType];
}

NSURL* getResourceUrl(NSString* basePath, NSString* resName, NSString* resType) {
    NSString* path = [NSString pathWithComponents:[NSArray arrayWithObjects:basePath, resName, nil]];
    return [[NSBundle mainBundle] URLForResource:path withExtension:resType];
}
