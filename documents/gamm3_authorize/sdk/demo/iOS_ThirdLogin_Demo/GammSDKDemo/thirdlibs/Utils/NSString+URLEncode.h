//
//  NSString+URLEncode.h
//
//  Created by Kevin Renskers on 31-10-13.
//  Copyright (c) 2013 Kevin Renskers. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (URLEncode)

- (NSString *)URLEncode;
- (NSString *)URLEncodeUsingEncoding:(NSStringEncoding)encoding;

- (NSString *)URLDecode;
- (NSString *)URLDecodeUsingEncoding:(NSStringEncoding)encoding;


/**
 encode 爱是怀疑.mkv字符串 http://hwpic.ztgame.com.cn/song/爱是怀疑.mkv
 */
- (NSString *)URLEncodeLastPathComponent;
@end
