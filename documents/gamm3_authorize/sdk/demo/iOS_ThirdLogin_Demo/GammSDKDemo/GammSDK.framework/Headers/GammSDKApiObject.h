//
//  GammSDKApiObject.h
//  GammSDK
//
//  Created by robin on 2017/11/8.
//  Copyright © 2017年 ztgame.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*
 * 错误码
 */
enum  GammSDKErrCode {
    GammSDKSuccess           = 0,    /**< 成功    */
    GammSDKErrCodeCommon     = -1,   /**< 普通错误类型    */
    GammSDKErrCodeUserCancel = -2,   /**< 用户点击取消并返回    */
    GammSDKErrCodeSentFail   = -3,   /**< 发送失败    */
    GammSDKErrCodeAuthDeny   = -4,   /**< 用户拒绝授权或授权失败  */
    GammSDKErrCodeUnsupport  = -5,   /**< 巨人账号管家不支持    */
};

#pragma mark - GammSDKBaseReq
/** 该类为巨人账号管家终端SDK所有请求类的基类 */
@interface GammSDKBaseReq : NSObject

/** 请求类型 */
@property (nonatomic, assign) int type;

@end

#pragma mark - GammSDKBaseResp
/** 该类为巨人账号管家终端SDK所有响应类的基类 */
@interface GammSDKBaseResp : NSObject

/** 错误码 */
@property (nonatomic, assign) int code;
/** 信息描述 */
@property (nonatomic, strong) NSString *msg;
/** 响应类型 */
@property (nonatomic, assign) int type;

@end

#pragma mark - GammSDKLoginReq
/*! @brief 第三方程序向巨人账号管家终端请求认证的消息结构
 *
 * 第三方程序要向巨人账号管家申请认证，并请求某些权限，需要调用GammSDKApi的sendReq成员函数，
 * 向巨人账号管家终端发送一个Req消息结构。巨人账号管家终端处理完后会向第三方程序发送一个处理结果。
 */
@interface GammSDKLoginReq : GammSDKBaseReq
/** 第三方程序本身用来标识其请求的唯一性，最后跳转回第三方程序时，由巨人账号管家终端回传。
 * @note state字符串长度不能超过1K
 */
@property (nonatomic, strong) NSString* state;
@end



#pragma mark - GammSDKLoginResp
/*! @brief 巨人账号管家处理完第三方程序的认证和权限申请后向第三方程序回送的处理结果。
 *
 * 第三方程序要向巨人账号管家申请认证，并请求某些权限，需要调用GammSDKApi的sendReq成员函数，向巨人账号管家终端发送一个Req消息结构。
 * 巨人账号管家终端处理完后会向第三方程序发送一个Resp。
 * @see onResp
 */
@interface GammSDKLoginResp : GammSDKBaseResp

/**
 获取accesstoken需要的code
 */
@property (nonatomic, strong) NSString* authCode;

/** 第三方程序本身用来标识其请求的唯一性，最后跳转回第三方程序时，由巨人账号管家终端回传。
 * @note state字符串长度不能超过1K
 */
@property (nonatomic, strong) NSString* state;
@end
