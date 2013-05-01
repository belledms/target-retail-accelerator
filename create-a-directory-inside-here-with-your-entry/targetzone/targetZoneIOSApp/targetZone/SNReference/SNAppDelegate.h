//
//  SNAppDelegate.h
//  SNReference
//
//  Created by Ryan Mannion on 11/17/11.
//  Copyright (c) 2011 Sonic Notify, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import "SNViewController.h"
#import <SonicUI/SonicUI.h>

@interface SNAppDelegate : NSObject <UIApplicationDelegate, UINavigationControllerDelegate, SonicUIDelegate> {
	SNViewController * _viewController;
    NSTimer *_timer;
}

@property (nonatomic, retain) IBOutlet UIWindow * window;
@property (nonatomic, retain) IBOutlet SNViewController * viewController;

#ifdef DEBUG_OVERLAY
- (void) setDebug:(NSString *) debug;
#endif

@end


