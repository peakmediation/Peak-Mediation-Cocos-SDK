//
//  PKEndPointEnvironment.h
//  Peak
//
//  Created by Oleksandr Shakhmin on 5/31/16.
//  Copyright © 2016 NIX. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM (NSUInteger, PKEndPointEnvironmentMode)
{
    PKEndPointEnvironmentModeLive,
    PKEndPointEnvironmentModeTest
};

@interface PKEndPointEnvironment : NSObject

@property(assign, nonatomic) PKEndPointEnvironmentMode mode;

+ (instancetype)sharedInstance;

@end
