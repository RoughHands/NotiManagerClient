//
//  NotiManagerClient.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#ifndef __NotiManagerClient__NotiManagerClient__
#define __NotiManagerClient__NotiManagerClient__

#include <string>

static const std::string DeviceInfoKey_AppName = "AppName";
static const std::string DeviceInfoKey_AppVersion = "AppVersion";
static const std::string DeviceInfoKey_DeviceToken = "DeviceToken";
static const std::string DeviceInfoKey_DeviceName = "DeviceName";
static const std::string DeviceInfoKey_DeviceModel = "DeviceModel";
static const std::string DeviceInfoKey_DeviceSystemVersion = "DeviceSystemVersion";
static const std::string DeviceInfoKey_IsPushBadgeOn = "isPushBadgeOn";
static const std::string DeviceInfoKey_IsPushAlertOn = "isPushAlertOn";
static const std::string DeviceInfoKey_IsPushSoundOn = "isPushSoundOn";
#define DeviceInfoKey(keyInString) [NSString stringWithUTF8String:DeviceInfoKey_##keyInString.c_str()]

class NotiManagerClient
{
private:
    static NotiManagerClient*   _SingletonInstance;
    
private:
    NotiManagerClient();
public:
    ~NotiManagerClient();
    
    static NotiManagerClient& GetInstance();
    
    void        RequestRegisterDeviceToken(std::string deviceInfoJSON);
    
    void        RequestSendPushNotification();
};




// To Do 1 : On AppCotroller app did finish lauching Add Below Codes
//
/*
    // NotiManager To Do : Push Notification
    // Add registration for remote notifications
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound)];
    application.applicationIconBadgeNumber = 0;

    return YES;
*/

// To Do 2 : And override this function on AppController
/*
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
    [deviceInfoDic setValue:appName forKey:@"AppName"];
    [deviceInfoDic setValue:appVersion forKey:@"AppVersion"];
    [deviceInfoDic setValue:devToken forKey:@"DeviceToken"];
//  [deviceInfoDic setValue:deviceUUID forKey:@"DeviceUUID"];
    [deviceInfoDic setValue:deviceName forKey:@"DeviceName"];
    [deviceInfoDic setValue:deviceModel forKey:@"DeviceModel"];
    [deviceInfoDic setValue:deviceSystemVersion forKey:@"DeviceSystemVersion"];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushBadgeOn] forKey:@"isPushBadgeOn"];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushAlertOn] forKey:@"isPushAlertOn"];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushSoundOn] forKey:@"PushSound"];
    
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
    
    #endif
}
*/

#endif /* defined(__NotiManagerClient__NotiManagerClient__) */
