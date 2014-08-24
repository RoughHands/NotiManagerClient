//
//  NotiManagerClient.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#ifndef __NotiManagerClient__NotiManagerClient__
#define __NotiManagerClient__NotiManagerClient__

#import <Foundation/Foundation.h>
//#include <string>
//
//static const std::string DeviceInfoKey_AppName = "AppName";
//static const std::string DeviceInfoKey_AppVersion = "AppVersion";
//static const std::string DeviceInfoKey_DeviceToken = "DeviceToken";
//static const std::string DeviceInfoKey_DeviceName = "DeviceName";
//static const std::string DeviceInfoKey_DeviceModel = "DeviceModel";
//static const std::string DeviceInfoKey_DeviceSystemVersion = "DeviceSystemVersion";
//static const std::string DeviceInfoKey_IsPushBadgeOn = "isPushBadgeOn";
//static const std::string DeviceInfoKey_IsPushAlertOn = "isPushAlertOn";
//static const std::string DeviceInfoKey_IsPushSoundOn = "isPushSoundOn";
//#define DeviceInfoKey(keyInString) [NSString stringWithUTF8String:DeviceInfoKey_##keyInString.c_str()]

static NSString* DeviceInfoKey_AppName = @"AppName";
static NSString* DeviceInfoKey_AppVersion = @"AppVersion";
static NSString* DeviceInfoKey_DeviceToken = @"DeviceToken";
static NSString* DeviceInfoKey_DeviceName = @"DeviceName";
static NSString* DeviceInfoKey_DeviceModel = @"DeviceModel";
static NSString* DeviceInfoKey_DeviceSystemVersion = @"DeviceSystemVersion";
static NSString* DeviceInfoKey_IsPushBadgeOn = @"isPushBadgeOn";
static NSString* DeviceInfoKey_IsPushAlertOn = @"isPushAlertOn";
static NSString* DeviceInfoKey_IsPushSoundOn = @"isPushSoundOn";



@interface NotiManagerClient : NSObject
+(NotiManagerClient*)getInstance;

-(void)InitializeService:(UIApplication*)uiApplication;

-(void)RequestRegisterDeviceToken:(NSData*) deviceToken;
-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge;
-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge launchImage:(NSString*)launchImage sound:(NSString*)sound;
-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge locKey:(NSString*)locKey lokArgs:(NSString*)locArgs actionLocKey:(NSString*)actionLocKey
                                    launchImage:(NSString*)launchImage sound:(NSString*)sound;
-(void)OnRegisterDeviceTokenCompleted:(NSData*)responseData;
-(void)OnSendPushNotificationCompleted:(NSData*)responseData;
@end // NotiRequest


// To Do 1 : On AppCotroller app did finish lauching Add Below Codes
//
/*
    // NotiManager To Do : Push Notification
    // Add registration for remote notifications 
    
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions )
    {
        ...
        ...
        [[NotiManagerClient getInstance] InitializeService:application];
        return YES;
    }
*/

// To Do 2 : And override this function on AppController
/*
// NotiManager To Do : Push Notification
// On AcceptPush Registration
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    #if !TARGET_IPHONE_SIMULATOR
    
    [[NotiManagerClient getInstance] RequestRegisterDeviceToken:deviceToken];
    
    [[NotiManagerClient getInstance] RequestSendPushNotification:@"Body11" badge:2 locKey:@"Loc Key" lokArgs:@"{}" actionLocKey:@"Loc Key" launchImage:@"" sound:@"default"];
    #endif
}
*/

#endif /* defined(__NotiManagerClient__NotiManagerClient__) */
