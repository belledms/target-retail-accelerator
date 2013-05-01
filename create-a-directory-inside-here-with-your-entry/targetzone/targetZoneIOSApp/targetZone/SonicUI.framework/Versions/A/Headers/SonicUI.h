//
//  SonicUI.h
//  sonicnotify
//
//  Created by Jonathan Glanz on 6/28/12.
//  Copyright (c) 2012 Densebrain, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Sonic.h"


//Notifications are used on delegate callbacks to enabled linked functionality
FOUNDATION_EXPORT NSString *const SonicContentTypeURL;
FOUNDATION_EXPORT NSString *const SonicContentTypeAutoEngageURL;
FOUNDATION_EXPORT NSString *const SonicContentTypeVideo;
FOUNDATION_EXPORT NSString *const SonicContentTypeAutoEngageVideo;
FOUNDATION_EXPORT NSString *const SonicContentTypeFile;


@class SonicUI;
@class SonicContentViewController;
@class SNContent;

/**
* Protocol that is implemented by any application that is using the builtin
* UI widgets provided by Sonic Notify, Inc
*/
@protocol SonicUIDelegate <NSObject>

@optional

/**
* Callback used to provide custom table cells for rendering custom content types
*
* @param sonicNotifyUI - the configured running instance of sonic notify ui
* @param tableView - the tableView that is rendering the cells
* @param content - that the cell will represent
*
* @return TableViewCell to be used in the rendering of content cells
 **/
- (UITableViewCell *) sonicUI: (SonicUI *)sonicUI tableView: (UITableView *) tableView cellForContent: (SNContent *) content;

/**
* Callback used to provide custom table cell height
*
* @param sonicNotifyUI - the configured running instance of sonic notify ui
* @param tableView - the tableView that is rendering the cells
* @param content - that the cell will represent
*
* @return CGFloat height of cell
 **/
- (CGFloat) sonicUI: (SonicUI *)sonicUI tableView: (UITableView *) tableView cellHeightForContent: (SNContent *) content;

/**
* Callback for a view that will be used to display custom content types
*
* @param sonicNotifyUI - the configured running instance of sonic notify ui
* @param content - content that needs to be displayed to the user
* @param contentViewController - the parent view controller that will hold the content view
*
* @return UIView - to display the content
**/
- (UIView *) sonicUI: (SonicUI *)sonicUI viewForContent: (SNContent *) content withViewController: (SonicContentViewController *) sonicContentViewController;


/**
* Callback to retrieve a resource filename for a sound that should be played when content is received
*
* @param sonicNotifyUI - instance that is configured and running
* @param content - content that is being schedule or that has been received
* @param soundUrl is the default url that has been created
*
* @return NSString - resource filename that should be played for content, if nil is returned then NO sound will be played
**/
- (NSURL *) sonicUI: (SonicUI *)sonicUI soundFileForContent: (SNContent *) content withDefaultUrl: (NSURL *) soundUrl;

/**
* Decorate the navigation controller, this is called before presenting the navigation controller through
* showContentNavigator
*
* @param sonicNotifyUI - instance that is configured and running
* @param navigationController - the controller to decorate
*
* @return the navigation controller that was decorated, this should usually be a reference to the navigation controller that was passed
*
*/

- (UINavigationController *) sonicUI: (SonicUI *)sonicUI decorateContentNavigationController: (UINavigationController *) navigationController;


/**
* Decorate the table view controller used for presenting a content list
*
*
* @param sonicNotifyUI - instance that is configured and running
* @param tableViewController - the controller to decorate
*
* @return the navigation controller that was decorated, this should usually be a reference to the navigation controller that was passed
*
*/

- (UITableViewController *) sonicUI: (SonicUI *)sonicUI decorateContentTableViewController: (UITableViewController *) tableViewController;

/**
* Decorate the content view controller
*
*
* @param sonicNotifyUI - instance that is configured and running
* @param contentViewController - the controller to decorate
*
* @return the decorator controller
*
*/

- (UIViewController *) sonicUI: (SonicUI *)sonicUI decorateContentViewController: (UIViewController *) contentViewController;



/**
* Decorate the split view controller (iPad Only), this is called before presenting the split view controller through
* showContentNavigator
*
* @param sonicNotifyUI - instance that is configured and running
* @param splitViewController - the controller to decorate
*
* @return the split view controller that was decorated, this should usually be a reference to the navigation controller that was passed
*
*/

- (UISplitViewController *) sonicUI: (SonicUI *)sonicUI decorateContentSplitViewController: (UISplitViewController *) splitViewController;


@end


@interface SonicUI : NSObject <SonicDelegate>

/** 
 Retrieve the shared UI class instance
 **/
+ (SonicUI *) sharedInstance;


/**
 Initialize the UI interface system
 
 @param applicationGuid - The unique identifier provided by the CMS
 @param delegate - Delegate for user interface call backs and decorations
 **/
- (id) initializeWithApplicationGUID: (NSString *) applicationGuid andDelegate: (id <SonicUIDelegate>) delegate;

/**
 Initialize the UI interface system
 
 @param applicationGuid - The unique identifier provided by the CMS
 @param delegate - Delegate for user interface call backs and decorations
 @param parentViewController - the view controller that will be used to present the modal Sonic Widgets from
 **/
- (id) initializeWithApplicationGUID: (NSString *) applicationGuid andDelegate: (id <SonicUIDelegate>) delegate andParentViewController: (UIViewController *) parentViewController;



/**
 Clear content notifications - these are local notifications that were delivered while the application was in the background
 **/
- (void) clearContentNotifications;


/**
 Schedule content notification configured to directly launch the content
 
 @param content - to generate the notification for.
 **/
- (void) scheduleContentNotification:(SNContent *) content;

/**
 didReceiveLocalNotification is a callback from an application to handle the local notification
 
 @param notification - UILocalNotification to handle
 
 @return BOOL - whether it was handled or not
 **/


- (BOOL) didReceiveLocalNotification: (UILocalNotification *) notification;

/**
* Show the content navigator as a modal view controller on the parent that was passed
* during the system initialization.
*/
- (void) showContentNavigator;

/**
* Close the content navigator modal view controller; simply calls dismiss on the parent
*
* @param animated whether or not the dismissal should be animated
*/
- (void) closeContentNavigator: (BOOL) animated;


/**
 Display a piece of content using in the standard content view framework
 
 @param content to be displayed
 
 **/
- (void) showContent: (SNContent *) content;

/**
 Utility method to make device vibrate
 **/
- (void) vibrate;

/**
* Used to retrieve the navigation controller being used for content widget management
*/
@property (nonatomic, retain, readonly) UINavigationController * contentNavigationController;

@end
