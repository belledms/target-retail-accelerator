//
//  Sonic.h
//  SonicNotify
//
//  Created by Ryan Mannion on 11/8/11.
//  Copyright (c) 2011 Sonic Notify, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 TWO METHODS OF ENTERING APP
 1     Exiting if APP exits without the Client calling stopListening(), then the app receives on background and will listen for 10 mins in background before killing itself
       TODO make sure that killing timer when entering foreground, so that not killing when reopened before 10 mins is over

 2     Entering while in location background-
       BGtask is immediately started and timer begins
       if criteria is not met, everything is killed including bgtask
       if criteria are met for Location Update, server is called, when server call ends, either success or failure,
       Add checks if currently listening, if it is then doesnt kill

**/


//Core Macros
#define SONIC_DEPRECATED __attribute__((deprecated))

//Notifications are used on delegate callbacks to enabled linked functionality
FOUNDATION_EXPORT NSString *const SonicNotificationDidHearCode;
FOUNDATION_EXPORT NSString *const SonicNotificationDidReceiveActications;
FOUNDATION_EXPORT NSString *const SonicNotificationPreferencesUpdated;
FOUNDATION_EXPORT NSString *const SonicNotificationReset;
FOUNDATION_EXPORT NSString *const SonicNotificationRegionUpdated;
FOUNDATION_EXPORT NSString *const SonicUserInfoContentId;

//Declare these classes as they are used in delegates
@class Sonic;
@class SNContent;

/**
* Sonic delegate used for responding to sonic events, it includes several core functions
*
* - Responding to the fact that a signal is in range
* - Responding to a specific signal with the appropriate time index relative to the program
* - Respond to receiving activations (content)
* - Respond to content being deleted
* - Respond to offline content caching
*
*/
@protocol SonicDelegate <NSObject>
@optional

/**
* This is called when a sonic signal is heard
*
* NOTE: this does not mean content is available
*
* @param sonic instance that heard the signal
*
* @return whether or not you are interested in receiving content for this signal, it is the implementers responsibility for throttling
*
* @see URL#sonic:didHearCode:withTimeInterval
*/
- (BOOL) sonicDidHearCode: (Sonic *)sonic SONIC_DEPRECATED;

/**
* This is called when a sonic signal is heard with the code that was heard
*
* NOTE: this does not mean content is available
*
* @param sonic instance that heard the signal
* @param code that was heard
*
* @return whether or not you are interested in receiving content for this signal, it is the implementers responsibility for throttling
*
* @see URL#sonic:didHearCode:withTimeInterval
*/
- (BOOL) sonicDidHearCode: (Sonic *)sonic withValue: (NSNumber *) code SONIC_DEPRECATED;


/**
* This is called when a sonic signal is heard and provides a GUID which is specific to this particular signal
* only during the currently running process and provides the time interval as well if the signal has relative time.
*
* NOTE: this does not mean content is available
*
* @param sonic instance that heard the signal
* @param codeGuid unique identifier for this signal that is only good for the current process
* @param timeInterval the relative time interval for the current signal (if applicable, i.e. movies, tv, etc)
*
* @return whether or not you are interested in receiving content for this signal, it is the implementers responsibility for throttling
*
*/
- (BOOL) sonic: (Sonic *)sonic didHearCode: (NSString *) codeGuid withTimeInterval: (NSNumber *) timeInterval;

/**
* Did receive activations is called after URL#sonic:didHearCode:withTimeInterval returns YES.
*
* The server is then queried (or offline content prepared) and activations delivered
*
* @param sonic instance that received content
* @param activations instances of SonicActivation that contain, delivery time, content, etc
*/
- (void) sonic: (Sonic *)sonic didReceiveActivations: (NSArray *) activations;

/**
* When offline content is receive by Sonic and cached internally (sonic only caches the raw data)
* it is then passed to the delegate to have the implementing system cache whatever data is required.
*
* @param sonic instance that received content
* @param contents is an array of SNContent that needs to have application level caching completed
*/
- (void) sonic: (Sonic *)sonic cacheOfflineContent: (NSArray *) contents;

/**
* When content is no longer required to be cached this method is executed for individual pieces of content
*
* @param sonic instance that received content
* @param identifier for content, this will match the SNContent.identifier value provided in cacheOfflineContent
*/
- (void) sonic: (Sonic *)sonic deletedContentWithIdentifier: (NSInteger) identifier;

@end    

@interface Sonic : NSObject

/**
* Get the Sonic singleton to execute operations on
*
* @return Sonic singleton reference
*/
+ (Sonic *) sharedInstance;

/**
* Initialize the sonic system with the application guid and a delegate that will receive all callbacks.
*
* @param applicationGuid unique identifier provided by Sonic
* @param delegate for Sonic callbacks
*/
- (void) initializeWithApplicationGUID: (NSString *) applicationGuid andDelegate: (id <SonicDelegate>) delegate;


/**
* Start audio sampling
*
* @return whether or not listening began
*/
- (BOOL) startListening;

/**
* Stop audio sampling
*/
- (void) stopListening;

/**
* Mark an activation as engaged
*
* @param content that was engaged
*/
- (void) engagedContent: (SNContent *) content;

/**
* Set the remote notification token provided by apple in order to support push notifications
*/
- (void) setRemoteNotificationToken: (NSData *) tokenData;

/**
* Callback when an application receives a remote push notification
*
* @param userInfo received from apple containing the payload
*/
- (void) didReceiveRemoteNotification: (NSDictionary *) userInfo;

/**
* Reset all content, activations, cached content, etc
*/
- (void) reset;


- (NSString *) workingDirectory;

/**
* All of the current content in the system including non active content
*/
@property (nonatomic, readonly) NSArray * allContent;

/**
* All of the active, triggered content in the system
*/
@property (nonatomic, readonly) NSArray * allActiveContent;

/**
* The delegate that was initialized with the Sonic system
*/
@property (nonatomic, retain, readonly) id <SonicDelegate> delegate;

/**
* Access the unique identifier for this device (NOT UDID)
*/
@property (nonatomic, retain, readonly) NSString * uuid;


@end
