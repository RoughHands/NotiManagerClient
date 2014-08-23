/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#include "NotiManagerClient.h"


@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();
    
    // NotiManager To Do : Push Notification
    // Add registration for remote notifications
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound)];
    application.applicationIconBadgeNumber = 0;

    return YES;
}


// NotiManager To Do : Push Notification
// On AcceptPush Registration
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    #if !TARGET_IPHONE_SIMULATOR
    NSString *appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
 
    NSUInteger rntypes = [[UIApplication sharedApplication] enabledRemoteNotificationTypes];
 
    BOOL isPushBadgeOn = NO;
    BOOL isPushAlertOn = NO;
    BOOL isPushSoundOn = NO;
 
    if( (rntypes & UIRemoteNotificationTypeBadge) != UIRemoteNotificationTypeNone )
    {
        isPushBadgeOn = YES;
    }
    if( (rntypes & UIRemoteNotificationTypeAlert) != UIRemoteNotificationTypeNone )
    {
        isPushAlertOn = YES;
    }
    if( (rntypes & UIRemoteNotificationTypeSound) != UIRemoteNotificationTypeNone )
    {
        isPushSoundOn = YES;
    }
    
    UIDevice *dev = [UIDevice currentDevice];
//    NSString *deviceUuid = [self uniqueDeviceIdentifier];
    NSString *deviceName = dev.name;
    NSString *deviceModel = dev.model;
    NSString *deviceSystemVersion = dev.systemVersion;
    NSString *devToken = [[[[deviceToken description] stringByReplacingOccurrencesOfString:@"<" withString:@""] stringByReplacingOccurrencesOfString:@">" withString:@""] stringByReplacingOccurrencesOfString:@" " withString:@""];
 
    // Build URL String for Registration
    NSMutableDictionary* deviceInfoDic = [[NSMutableDictionary alloc] init];
    [deviceInfoDic setValue:appName forKey:DeviceInfoKey(AppName)];
    [deviceInfoDic setValue:appVersion forKey:DeviceInfoKey(AppVersion)];
    [deviceInfoDic setValue:devToken forKey:DeviceInfoKey(DeviceToken)];
//  [deviceInfoDic setValue:deviceUUID forKey:@"DeviceUUID"];
    [deviceInfoDic setValue:deviceName forKey:DeviceInfoKey(DeviceName)];
    [deviceInfoDic setValue:deviceModel forKey:DeviceInfoKey(DeviceModel)];
    [deviceInfoDic setValue:deviceSystemVersion forKey:DeviceInfoKey(DeviceSystemVersion)];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushBadgeOn] forKey:DeviceInfoKey(IsPushBadgeOn)];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushAlertOn] forKey:DeviceInfoKey(IsPushAlertOn)];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushSoundOn] forKey:DeviceInfoKey(IsPushSoundOn)];
    
    NSError* nsError = nil;
    NSData* deviceInfoJSONData = [NSJSONSerialization dataWithJSONObject:deviceInfoDic options:NSJSONWritingPrettyPrinted error:&nsError];

    NSString* deviceInfoJSONString = nil;
    if( !deviceInfoJSONData )
    {
        NSLog(@"JSON Serialization Error : %@", nsError.localizedDescription);
        deviceInfoJSONString = [[NSString alloc] initWithString:@"{}"];
    }
    else
    {
        deviceInfoJSONString = [[NSString alloc] initWithData:deviceInfoJSONData encoding:NSUTF8StringEncoding];
    }
    
    std::string deviceInfoJSONStringC = [deviceInfoJSONString UTF8String];
    NotiManagerClient::GetInstance().RequestRegisterDeviceToken(deviceInfoJSONStringC);
    
    
    
    
    
    
    // TEST
    NSMutableDictionary* notiMessageDic = [[NSMutableDictionary alloc] init];
    [notiMessageDic setValue:@"message boddy" forKey:@"body"];
    [notiMessageDic setValue:@"action loc key" forKey:@"action_loc_key"];
    [notiMessageDic setValue:@"loc key" forKey:@"loc_key"];
    [notiMessageDic setValue:@"{}" forKey:@"loc_args"];
    [notiMessageDic setValue:@"" forKey:@"launch_image"];
    [notiMessageDic setValue:@"default" forKey:@"sound"];
    [notiMessageDic setValue:[NSNumber numberWithInt:2] forKey:@"badge"];
    
    NSData* notiMessageJSONData = [NSJSONSerialization dataWithJSONObject:notiMessageDic options:NSJSONWritingPrettyPrinted error:&nsError];
    
    NSString* notiMessageJSONString = nil;
    if( !notiMessageJSONData )
    {
        NSLog(@"JSON serialization Error : %@", nsError.localizedDescription);
        notiMessageJSONString=[[NSString alloc] initWithString:@"{}"];
    }
    else
    {
        notiMessageJSONString = [[NSString alloc] initWithData:notiMessageJSONData encoding:NSUTF8StringEncoding];
    }
    
    std::string notiMessageJSONStringC = [notiMessageJSONString UTF8String];
    NotiManagerClient::GetInstance().RequestSendPushNotification(notiMessageJSONStringC);
    
    #endif
}



- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}




#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
