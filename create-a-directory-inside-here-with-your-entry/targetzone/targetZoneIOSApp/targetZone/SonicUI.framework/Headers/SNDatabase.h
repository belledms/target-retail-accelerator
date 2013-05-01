//
//  SNDatabase.h
//  NewAPI
//
//  Created by Matt Isaacs on 11/5/12.
//  Copyright (c) 2012 Sonic Notify. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SNDatabase : NSObject
{
    NSManagedObjectContext *_managedObjectContext;
    NSManagedObjectModel *_managedObjectModel;
    NSPersistentStoreCoordinator *_persistentStoreCoordinator;
}

@property (readonly) NSManagedObjectContext *managedObjectContext;
@property (readonly) NSManagedObjectModel *managedObjectModel;
@property (readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;

- (void) reset;

@end
