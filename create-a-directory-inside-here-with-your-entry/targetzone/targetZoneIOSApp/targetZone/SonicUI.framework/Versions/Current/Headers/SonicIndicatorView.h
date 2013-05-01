//
//  SonicIndicatorView.h
//  sonicnotify
//
//  Created by Jonathan Glanz on 6/28/12.
//  Copyright (c) 2012 Sonic Notify, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
* SonicNotifyIndicatorView is a customizable view that is the entrance to the
* Sonic widget system for OOB application integration
*/
@interface SonicIndicatorView : UIButton

/**
* signalDetected can be polled for whether or not the signal has been heard in the past 3 seconds
*/
@property (readonly) BOOL signalDetected;

/**
* animateIndicator is a built-in animation that specifically pulses the images in the button.
*
*/
- (void) animateIndicator;


@end
