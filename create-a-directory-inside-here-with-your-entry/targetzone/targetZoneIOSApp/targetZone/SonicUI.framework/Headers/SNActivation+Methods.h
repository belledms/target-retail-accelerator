//
//  SNActivation+Methods.h
//  NewAPI
//
//  Created by Matt Isaacs on 11/7/12.
//  Copyright (c) 2012 Sonic Notify. All rights reserved.
//

#import "SNActivation.h"

@interface SNActivation (Methods)

+ (SNActivation *) getActivationWithGUID:(NSString *)guid context:(NSManagedObjectContext *)context;
+ (NSArray *) getActivationsWithContent:(SNContent *) content context:(NSManagedObjectContext *)context;

@end
