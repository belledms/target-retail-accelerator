//
//  SNAppDelegate+Tracking.m
//  SonicDemo
//
//  Created by Ryan Mannion on 10/7/11.
//  Copyright 2011 Densebrain, Inc. All rights reserved.
//

#import "SNAppDelegate.h"
#import "DBNetwork.h"

@implementation SNAppDelegate (Tracking)

- (void) trackWithDataString: (NSString *) dataString {
	NSDictionary * postValues = [NSDictionary dictionaryWithObjectsAndKeys: 
								 APP_ID, @"appId", 
								 self.sessionData.uuid, @"deviceId",
								 DEVICE_TYPE, @"deviceTypeAlias",
								 dataString, @"data",
								 nil];	
	
	NSString * url = [NSString stringWithFormat:@"%@/api/trackEvent", SN_SERVER_URL];
	NSDictionary * headers = [NSDictionary dictionaryWithObject:@"application/json" forKey:@"Content-Type"];
	
	[DBNetworkManager uploadManagerDynamicURI:url
								  withTimeout:SN_TIMEOUT
								   andRawPost:[[postValues JSONRepresentation] dataUsingEncoding:NSUTF8StringEncoding]
							 andDynamicTarget:self
									onSuccess:@selector(trackSuccess:)
									onFailure:@selector(trackFailure:)
							   onSendProgress:nil
								  andUserInfo:nil
									   andTag:0
										isRaw:NO
						   withAuthentication:nil
									 headOnly:NO
									  headers:headers
	 ];
}

- (void) trackSuccess: (DBUploadResult *) result {
	NSDictionary * data = [result.response JSONValue];
	LOG(@"Success: %@", data);
}

- (void) trackFailure: (DBUploadResult *) result {
}

@end
