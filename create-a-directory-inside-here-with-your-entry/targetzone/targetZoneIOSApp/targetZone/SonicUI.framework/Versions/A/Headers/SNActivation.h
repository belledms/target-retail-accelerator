//
//  SNActivation.h
//  sonicnotify
//
//  Created by Matt Isaacs on 2/6/13.
//  Copyright (c) 2013 Sonic Notify, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class SNContent;

@interface SNActivation : NSManagedObject

@property (nonatomic, retain) NSNumber * engaged;
@property (nonatomic, retain) NSString * guid;
@property (nonatomic, retain) NSNumber * code;
@property (nonatomic, retain) NSNumber * timeIndex;
@property (nonatomic, retain) SNContent *content;

@end
