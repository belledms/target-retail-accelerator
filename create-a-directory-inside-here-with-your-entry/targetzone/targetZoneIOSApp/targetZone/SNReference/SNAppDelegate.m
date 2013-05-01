//
//  SNAppDelegate.m
//  SNReference
//
//  Created by Ryan Mannion on 11/17/11.
//  Copyright (c) 2011 Sonic Notify, Inc. All rights reserved.
//

#import "SNAppDelegate.h"
//#import "SNContent+Methods.h"
#import "SonicUI/SonicContentViewController.h"
//#import "DCIntrospect.h"

#ifdef PUSHER
#import "SNDebugManager.h"
#import "SonicContent.h"
#import "SonicContentViewController.h"
#endif

#ifdef DEBUG
#define LOG(format, ...) NSLog(format, ## __VA_ARGS__)
#else
#define LOG(format, ...) 
#endif


//#define SONIC_APP_ID @"YmYyMmJmMzEtZTZmMC00MzgyLWIwMzYtMjVjY2E0YmNkNTIw"
//#define SONIC_APP_ID @"Mjg2MzIxNWYtM2NhMC00NmVmLTljZWYtZDUwYmFiMmZlMjJk" //moses
//#define SONIC_APP_ID @"MWZlMTY4NDUtMzk0ZS00ZmU1LWExMWQtMTMwZTk1ZjhjOGJl"
//#define SONIC_APP_ID @"MDMxMzkzODMtMTQ3Yi00YzQ1LWJhMjYtZDU2YmExYjkxZjhi"
//#define SONIC_APP_ID @"NmJmNGU5NmItMjQyZS00MDNlLWIzYmMtMjk0YTAzZjRiNzVk"
//#define SONIC_APP_ID @"123456"
//#define SONIC_APP_ID @"M2MxODlmZGUtM2I2Yy00NDY5LWEyNmUtZjJhYWFlNmFjMDMx"
#define SONIC_APP_ID @"YmE2YmMyMzUtM2E3OC00NzM0LWFlMjgtMGJlMWI5MWUzYjZh"

#define UIColorFromRGB(rgbValue) \
[UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0x00FF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0x0000FF))/255.0 \
alpha:1.0]


@implementation SNAppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;


/**
* Application entrance point
*
* @param launchOptions includes a disctionary of all the parameters used for launch
*/
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    
    NSDictionary *defaults = [NSDictionary dictionaryWithObject:SONIC_APP_ID forKey:@"sonicAppID"];
    [[NSUserDefaults standardUserDefaults] registerDefaults:defaults];
    
    NSString *appID = [[NSUserDefaults standardUserDefaults] stringForKey:@"sonicAppID"];
    [[SonicUI sharedInstance] initializeWithApplicationGUID:appID
                                                      andDelegate:self 
                                          andParentViewController: self.viewController];
    

    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge |UIRemoteNotificationTypeSound)];



    [self.window setRootViewController:self.viewController];
    [self.window makeKeyAndVisible];
    
#if TARGET_IPHONE_SIMULATOR
    //[[DCIntrospect sharedIntrospector] start];
#else
    self.viewController.debugButton.hidden = YES;
#endif
	return YES;
}





//Cleanup and kill
- (void)dealloc {
	self.window = nil;
    self.viewController = nil;
	
	[super dealloc];
}




#pragma mark Remote/Local Notification configuration



#pragma mark Sonic Notify UI Delegate Implementation

- (UITableViewCell *) sonicUI: (SonicUI *)sonicUI tableView: (UITableView *) tableView cellForContent: (SNContent *) content {
    /*
    SonicContentTableViewCell * cell = (SonicContentTableViewCell *)[tableView dequeueReusableCellWithIdentifier:@"cell"];
    
    if (cell == nil) {
        cell = [[[SonicContentTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"] autorelease];
    }
    
    
    cell.content = content;
    */
     
    if ([content.alias isEqualToString:@"MRAID"]){
        NSLog(@"Table View");
        SonicAdView * tableCellView = [[[SonicAdView alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"] autorelease];
        //tableCellView.delegate = self;
        NSURL * url = [NSURL URLWithString:[[content fieldsDictionary] valueForKey:@"URL"]];
        tableCellView.creativeUrl = url;
        if ([tableCellView loadCreativeFromURL:url])
            NSLog(@"Loaded URL for MRAID");
        
        return tableCellView;

    }
    else {
        return nil;
    }
     
   // return cell;
}

- (CGFloat) sonicUI: (SonicUI *)sonicUI tableView: (UITableView *) tableView cellHeightForContent: (SNContent *) content {
    return 142.0;
}

- (UINavigationController *) sonicUI: (SonicUI *) sonicUI decorateContentNavigationController: (UINavigationController *) navigationController {
    

    navigationController.navigationItem.title = @"My Cart";

    navigationController.navigationBar.barStyle = UIBarStyleBlackOpaque;
    navigationController.navigationBar.tintColor = UIColorFromRGB(0xed1c24);

    return navigationController;
}

- (void) onTimerFired: (NSTimer *) timer {
    [[Sonic sharedInstance] simulateBeaconCode:1000002];
}

@end
