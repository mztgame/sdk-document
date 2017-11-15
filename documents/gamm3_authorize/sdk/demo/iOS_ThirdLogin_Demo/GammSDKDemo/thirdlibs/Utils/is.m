//
//  is.m
//  GiantAssistant
//
//  Created by robin on 2017/9/25.
//  Copyright © 2017年 Giant. All rights reserved.
//

#import "is.h"

/** 删除字符串空白行 */
NSString* trimString(NSString* input) {
    NSMutableString *mStr = [input mutableCopy];
    CFStringTrimWhitespace((CFMutableStringRef)mStr);
    NSString *result = [mStr copy];
    mStr = nil;
    return result;
}

BOOL isNull(id object){
    return (nil == object || [object isKindOfClass:[NSNull class]]);
}

BOOL isEmptyString(NSString* object){
    if (isNull(object)) {
        return YES;
    }
    
    return ([trimString(object) length] <= 0);
}

BOOL isEmptyDictionary(NSDictionary *object){
    if (isNull(object)) {
        return YES;
    }
    
    return ([object count] <= 0);
}

BOOL isEmptyArray(NSArray *object){
    if (isNull(object)) {
        return YES;
    }
    
    return ([object count] <= 0);
}

BOOL isOutOfArrayIndex(NSArray *object,NSInteger index){
    if (isEmptyArray(object)) {
        return YES;
    }
    
    return (index < 0 || index >= [object count]);
}

BOOL isDoubleEqualZero(double x){
    return (fabs(x) < DBL_EPSILON);
}

BOOL isFloatEqualZero(float x){
    return (fabs(x) < FLT_EPSILON);
}

BOOL isContainString(NSString *originString, NSString *subString){
    if(!isEmptyString(originString) && [originString rangeOfString:subString].location != NSNotFound){
        return YES;
    }else{
        return NO;
    }
}
