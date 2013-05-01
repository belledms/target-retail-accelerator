//
//  SNContent.h
//  sonicnotify
//
//  Created by Matt Isaacs on 3/4/13.
//  Copyright (c) 2013 Sonic Notify, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class SNActivation, SNSchedule;

@interface SNContent : NSManagedObject

@property (nonatomic, retain) NSString * alias;
@property (nonatomic, retain) NSDate * deployDate;
@property (nonatomic, retain) NSData * fields;
@property (nonatomic, retain) NSNumber * identifier;
@property (nonatomic, retain) NSNumber * isActivated;
@property (nonatomic, retain) NSNumber * isDeployed;
@property (nonatomic, retain) NSDate * lastUpdated;
@property (nonatomic, retain) NSString * state;
@property (nonatomic, retain) NSNumber * programId;
@property (nonatomic, retain) SNActivation *activation;
@property (nonatomic, retain) NSSet *schedules;
@end

@interface SNContent (CoreDataGeneratedAccessors)

- (void)addSchedulesObject:(SNSchedule *)value;
- (void)removeSchedulesObject:(SNSchedule *)value;
- (void)addSchedules:(NSSet *)values;
- (void)removeSchedules:(NSSet *)values;

@end
