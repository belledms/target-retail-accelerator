//
//  SNContent+Methods.h
//  NewAPI
//
//  Created by Matt Isaacs on 11/6/12.
//  Copyright (c) 2012 Sonic Notify. All rights reserved.
//

#import "SNContent.h"

@interface SNContent (Methods)

+ (void) loadContentsFromArray:(NSArray *)contents withContext:(NSManagedObjectContext *)context;
+ (NSArray *) allContentInContext:(NSManagedObjectContext *)context;
+ (NSArray *) allActiveContentInContext:(NSManagedObjectContext *)context;
+ (SNContent *) getContentWithID:(NSNumber *)contentID context:(NSManagedObjectContext *)context;

- (void) populateWithDictionary:(NSDictionary *)contentDictionary;
- (NSDictionary *) fieldsDictionary;

@end
