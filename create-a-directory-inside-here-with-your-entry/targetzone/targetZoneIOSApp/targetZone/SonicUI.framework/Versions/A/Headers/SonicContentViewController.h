//
//  SLContentViewController.h
//  SonicDemo
//
//  Created by Ryan Mannion on 10/6/11.
//  Copyright 2011 Sonic Notify, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import "SNContent+Methods.h"

@class SonicContent;
@class SonicContentViewController;

typedef enum {
    SonicContentViewControllerStateUnknown,
    SonicContentViewControllerStateLoading,
    SonicContentViewControllerStateLoaded,
    SonicContentViewControllerStateFailed
} SonicContentViewControllerState;


@interface SonicContentViewController : UIViewController <UINavigationControllerDelegate>

/**
* Set content with the option to animate the transition
*
* @param aContent to display
* @param animated whether or not to animate the transition
*/
- (void)setContent:(SNContent *)aContent animated: (BOOL) animated;

/**
* Content state, whether or not content has been loaded
*/
@property (nonatomic, assign) SonicContentViewControllerState state;

/**
* Used to set and retrieve the current content being displayed
*/
@property (nonatomic, retain) SNContent * content;

/**
* Parses a query string into a dictionary.  This is used for JavaScript callbacks
*
* @param queryString to parse
*
* @return dictionary of key value pairs from the query string
*/
- (NSDictionary *) parseKeyValuesFromQueryString: (NSString *) queryString;


/**
* The internal webview that is being used to display the content
*/
@property (nonatomic, retain) UIWebView * webView;

@property (nonatomic, retain) MPMoviePlayerViewController *movieViewController;

@end


