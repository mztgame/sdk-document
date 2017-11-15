//
//  is.h
//  GiantAssistant
//
//  Created by robin on 2017/9/25.
//  Copyright © 2017年 Giant. All rights reserved.
//

#import <Foundation/Foundation.h>

/** 判断是否为空 */
BOOL isNull(id object);
BOOL isEmptyString(NSString* object);
BOOL isEmptyDictionary(NSDictionary *object);
BOOL isEmptyArray(NSArray *object);

/** 判断索引越界 */
BOOL isOutOfArrayIndex(NSArray *object,NSInteger index);

/** 检测float==0 */
BOOL isDoubleEqualZero(double value);
BOOL isFloatEqualZero(float x);

/** 是否包含指定字符串 */
BOOL isContainString(NSString *originString, NSString *subString);
