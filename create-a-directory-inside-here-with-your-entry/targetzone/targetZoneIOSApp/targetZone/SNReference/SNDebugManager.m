//
// Created by jglanz on 7/4/12.
//
// To change the template use AppCode | Preferences | File Templates.
//

#ifdef PUSHER
#import "SNDebugManager.h"

#import "PTPusher.h"
#import "Sonic+Private.h"
#import "PTPusherEvent.h"

static SNDebugManager * gInstance;

@interface SNDebugManager() <PTPusherDelegate> {
    PTPusher * _client;
}

@property (nonatomic, retain) PTPusher * client;

@end

@implementation SNDebugManager {

}

@synthesize client = _client;

+ (void) start {
    gInstance = [[SNDebugManager alloc] init];
}

- (id) init {
    self = [super init];
    if (self) {
        self.client = [PTPusher pusherWithKey:@"1b971e4a21319f1550c7" delegate:self encrypted: YES];
        [self.client subscribeToChannelNamed:@"debug"];
        [self.client bindToEventNamed:@"simulate-beacon" target:self action:@selector(eventSimulateBeaconCode:)];
    }
    return self;
}

- (void) eventSimulateBeaconCode: (PTPusherEvent *) event {
    if ([event.data isKindOfClass:[NSDictionary class]]) {
        NSDictionary * data = event.data;
        NSNumber * codeObj = [data objectForKey:@"code"];
        NSInteger code = [codeObj integerValue];
        if (codeObj && code > 0) {
            NSLog(@"Simulate code: %i", code);
            [[Sonic sharedInstance] simulateBeaconCode:code];
        }
    }

}

@end

#endif