//
//  SLActivationsViewController.h
//  SonicDemo
//
//  Created by Jonathan Glanz on 10/6/11.
//  Copyright 2012 Sonic Notify, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SonicContentTableViewController : UITableViewController

/**
 * Manages the data available to the table, SNContent instances
 */
@property (nonatomic, readonly) NSArray * contents;
@property (nonatomic, retain) id<SonicUIDelegate> delegate;

@end


