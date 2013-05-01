//
//  SNViewController.h
//  SNReference
//
//  Created by Jonathan Glanz on 07/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SonicAdView.h>


@interface SNViewController : UIViewController<UIAlertViewDelegate, MRAdViewDelegate> {
    UIView * _infoOverlayView;
    UIButton * _debugButton;
    
}

@property (nonatomic, retain) IBOutlet UIView * infoOverlayView;
@property (nonatomic, retain) IBOutlet UIButton * debugButton;
@property (nonatomic, retain) IBOutlet SonicAdView *adView;

- (IBAction)reloadAd: (id) sender;
- (IBAction)infoButtonPressed:(id)sender;
- (IBAction)infoCloseButtonPressed:(id)sender;
- (IBAction)resetButtonPressed:(id)sender;
- (IBAction)appidButtonPressed:(id)sender;

@end
