//
//  SNViewController.m
//  SNReference
//
//  Created by Jonathan Glanz on 07/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SNViewController.h"

@interface SNViewController () <UIActionSheetDelegate>

@end

@implementation SNViewController

@synthesize infoOverlayView = _infoOverlayView;
@synthesize debugButton = _debugButton;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.infoOverlayView.alpha = 0;
    self.view.autoresizesSubviews = YES;
    self.adView.delegate = self;
    self.adView.parentViewController = self;
    
#ifdef DEBUG
    self.debugButton.hidden = NO;
#else
    self.debugButton.hidden = YES;
#endif
    [NSTimer scheduledTimerWithTimeInterval:10.0
                                     target:self
                                   selector:@selector(reloadAdAlex)
                                   userInfo:nil
                                    repeats:YES];// TODO remove
    //[self.adView loadCreativeFromURL:[NSURL URLWithString:@"http://10.0.1.114/~misaacs/ormma-read-only/WebTester/safari/ormma-test-ad-level-2.html"]];
    //[self reloadAd:nil];
}



- (void)viewDidUnload
{
    [super viewDidUnload];

}

- (NSUInteger) supportedInterfaceOrientations
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        return UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
    } else {
        return UIInterfaceOrientationMaskPortrait;
    }
}

- (BOOL) shouldAutorotate
{
    return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        return UIInterfaceOrientationIsLandscape(interfaceOrientation);
    } else {
        return UIInterfaceOrientationIsPortrait(interfaceOrientation);
    }
}

- (void)reloadAdAlex {
    //
    //
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
    [[NSURLCache sharedURLCache] setDiskCapacity:0];
    [[NSURLCache sharedURLCache] setMemoryCapacity:0];
    if (self.adView.creativeUrl) {
        NSURL * url = [self.adView.creativeUrl retain];
        self.adView.creativeUrl = nil;
        [self.adView loadCreativeFromURL:url];
        [url release];
    }
    
}

- (IBAction)reloadAd:(id)sender {
    //
    //
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
    
    if (self.adView.creativeUrl) {
        NSURL * url = [self.adView.creativeUrl retain];
        self.adView.creativeUrl = nil;
        [self.adView loadCreativeFromURL:url];
        [url release];
    }

}

- (IBAction)infoButtonPressed:(id)sender {
    
    [UIView animateWithDuration:0.3 animations:^{
        self.infoOverlayView.alpha = 1;
    }];
}

- (IBAction)infoCloseButtonPressed:(id)sender {
    [UIView animateWithDuration:0.3 animations:^{
        self.infoOverlayView.alpha = 0;
    }];
}

- (IBAction) debugButtonPressed: (id) sender {
    UIActionSheet * actionSheet = [[[UIActionSheet alloc] initWithTitle:@"Debug" delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:@"Simulate Beacon", nil] autorelease];
    
    [actionSheet showInView:self.view];
}

- (IBAction)resetButtonPressed:(id)sender {
    [[Sonic sharedInstance] reset];
    [self.adView loadCreativeFromURL:[NSURL URLWithString:@"about:blank"]];
    [self infoCloseButtonPressed:nil];
}

- (IBAction)appidButtonPressed:(id)sender
{
    UIAlertView *appIDAlertView = [[UIAlertView alloc] initWithTitle:@"Application GUID" message:@"Enter new Application GUID." delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Register",nil];
    appIDAlertView.alertViewStyle = UIAlertViewStylePlainTextInput;
    appIDAlertView.tag = 2;
    [appIDAlertView show];
    [appIDAlertView release];
}

- (void) dealloc {
    self.infoOverlayView = nil;
    self.debugButton = nil;
    
    [super dealloc];
}

- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1 && alertView.tag == 2) {
        [[Sonic sharedInstance] reset];
        NSString *appID = [alertView textFieldAtIndex:0].text;
        [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"sonicAccessKey"];
        [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"sonicSecretKey"];

        [[SonicUI sharedInstance] initializeWithApplicationGUID:appID
                                                    andDelegate:(id<SonicUIDelegate>)[[UIApplication sharedApplication] delegate]
                                        andParentViewController: self];
        [[NSUserDefaults standardUserDefaults] setObject:appID forKey:@"sonicAppID"];
    } else if (buttonIndex == 1 && alertView.tag == 1) {
        NSString *codeStr = [alertView textFieldAtIndex:0].text;
        
        NSNumberFormatter * f = [[[NSNumberFormatter alloc] init] autorelease];
        [f setNumberStyle:NSNumberFormatterDecimalStyle];
        NSNumber * code = [f numberFromString: codeStr];
        
        [[Sonic sharedInstance] simulateBeaconCode: [code unsignedIntValue]];
  
    }
}

- (UIViewController *)viewControllerForPresentingModalView{
    return self;

}

- (void)closeButtonPressed {
    NSLog(@"Closed.");
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == actionSheet.cancelButtonIndex)
        [actionSheet dismissWithClickedButtonIndex:buttonIndex animated:YES];
    
    if (buttonIndex == actionSheet.firstOtherButtonIndex) {
        UIAlertView * simulateAlertView = [[UIAlertView alloc] initWithTitle:@"Beacon Code" message:@"Enter beacon code." delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Send",nil];
        simulateAlertView.alertViewStyle = UIAlertViewStylePlainTextInput;
        simulateAlertView.tag = 1;
        [simulateAlertView show];
        [simulateAlertView release];
    }
}

@end
