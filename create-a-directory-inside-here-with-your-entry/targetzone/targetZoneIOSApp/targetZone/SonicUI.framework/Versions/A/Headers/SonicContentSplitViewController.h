//
//  SLSplitViewController.h
//  SonicDemo
//
//  Created by Ryan Mannion on 10/6/11.
//  Copyright 2011 Sonic Notify, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SonicUI.h"
#import "SonicContentTableViewController.h"
#import "SonicContentViewController.h"



@interface SonicContentSplitViewController : UISplitViewController<UIActionSheetDelegate>

- (id) initWithSonicUI: (SonicUI *) sonicUI;

@property (nonatomic, retain, readonly) UINavigationController * contentTableNavigationController;
@property (nonatomic, retain, readonly) UINavigationController * contentNavigationController;

@end
