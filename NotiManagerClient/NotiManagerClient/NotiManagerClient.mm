//
//  NotiManagerClient.mm
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#import "NotiManagerClient.h"
#import "SMWebRequest.h"

@implementation NotiManagerClient
-(id)init
{
    if( self = [super init] )
    {
    }
    return self;
}

-(void)dealloc
{
    [super dealloc];
}

+(NotiManagerClient*)getInstance
{
    static NotiManagerClient* _singletonInstance = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        _singletonInstance = [[NotiManagerClient alloc] init];
        [_singletonInstance retain];
    });
    
    return _singletonInstance;
}

-(void)InitializeService:(UIApplication*)uiApplication
{
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound)];
    uiApplication.applicationIconBadgeNumber = 0;
}


-(void)RequestRegisterDeviceToken:(NSData*) deviceToken
{
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
    [deviceInfoDic setValue:appName forKey:DeviceInfoKey_AppName];
    [deviceInfoDic setValue:appVersion forKey:DeviceInfoKey_AppVersion];
    [deviceInfoDic setValue:devToken forKey:DeviceInfoKey_DeviceToken];
//  [deviceInfoDic setValue:deviceUUID forKey:@"DeviceUUID"];
    [deviceInfoDic setValue:deviceName forKey:DeviceInfoKey_DeviceName];
    [deviceInfoDic setValue:deviceModel forKey:DeviceInfoKey_DeviceModel];
    [deviceInfoDic setValue:deviceSystemVersion forKey:DeviceInfoKey_DeviceSystemVersion];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushBadgeOn] forKey:DeviceInfoKey_IsPushBadgeOn];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushAlertOn] forKey:DeviceInfoKey_IsPushAlertOn];
    [deviceInfoDic setValue:[NSNumber numberWithBool:isPushSoundOn] forKey:DeviceInfoKey_IsPushSoundOn];
    
    NSError* nsError = nil;
    NSData* deviceInfoJSONData = [NSJSONSerialization dataWithJSONObject:deviceInfoDic options:NSJSONWritingPrettyPrinted error:&nsError];
    
    if( nsError != nil )
    {
        NSLog(@"Malformed Json Dic, [%@] [%s]", nsError.localizedDescription, __FUNCTION__);
        NSAssert2(nsError!=nil, @"Malformed Json Dic, [%@] [%s]", nsError.localizedDescription, __FUNCTION__);
        return;
    }

    SMWebRequest* request = [SMWebRequest requestWithURL:[NSURL URLWithString:@"http://121.162.245.166:2963/PushNoti/RegisterNewUser"]];
    
    [request addTarget:self action:@selector(OnRegisterDeviceTokenCompleted:) forRequestEvents:SMWebRequestEventComplete];
    [request setHTTPMethod:HTTPMethod_POST];
    [request setValue:@"application/json; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPBody:deviceInfoJSONData];

    [request start];
}

-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge
{
    [self RequestSendPushNotification:notiBody badge:badge locKey:@"" lokArgs:@"" actionLocKey:@"" launchImage:@"" sound:@"default"];
}

-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge launchImage:(NSString*)launchImage sound:(NSString*)sound
{
    [self RequestSendPushNotification:notiBody badge:badge locKey:@"" lokArgs:@"" actionLocKey:@"" launchImage:launchImage sound:sound];
}

-(void)RequestSendPushNotification:(NSString*)notiBody badge:(int)badge locKey:(NSString*)locKey lokArgs:(NSString*)locArgs actionLocKey:(NSString*)actionLocKey
                                    launchImage:(NSString*)launchImage sound:(NSString*)sound
{
    NSMutableDictionary* notiMessageDic = [[NSMutableDictionary alloc] init];
    [notiMessageDic setValue:notiBody forKey:@"body"];
    [notiMessageDic setValue:actionLocKey forKey:@"action_loc_key"];
    [notiMessageDic setValue:locKey forKey:@"loc_key"];
    [notiMessageDic setValue:locArgs forKey:@"loc_args"];
    [notiMessageDic setValue:launchImage forKey:@"launch_image"];
    [notiMessageDic setValue:sound forKey:@"sound"];
    [notiMessageDic setValue:[NSNumber numberWithInt:badge] forKey:@"badge"];
    
    NSError* nsError = nil;
    NSData* notiMessageJSONData = [NSJSONSerialization dataWithJSONObject:notiMessageDic options:NSJSONWritingPrettyPrinted error:&nsError];

    if( nsError != nil )
    {
        NSLog(@"Malformed Json Dic, [%@] [%s]", nsError.localizedDescription, __FUNCTION__);
        NSAssert2(nsError!=nil, @"Malformed Json Dic, [%@] [%s]", nsError.localizedDescription, __FUNCTION__);
        return;
    }
    
    SMWebRequest* request = [SMWebRequest requestWithURL:[NSURL URLWithString:@"http://121.162.245.166:2963/PushNoti/SendPushNotification"]];
    
    [request addTarget:self action:@selector(OnSendPushNotificationCompleted:) forRequestEvents:SMWebRequestEventComplete];
    [request setHTTPMethod:HTTPMethod_POST];
    [request setValue:@"application/json; charset=utf-8" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPBody:notiMessageJSONData];
    
    [request start];
}

-(void)OnRegisterDeviceTokenCompleted:(NSData*)responseData
{
    NSAssert1(responseData!=nil, @"Response Data Must not be nil, %s", __FUNCTION__);

    NSError* error=nil;
    NSDictionary* responseDictionary = [NSJSONSerialization JSONObjectWithData:responseData options:NSJSONReadingMutableLeaves|NSJSONReadingMutableContainers|NSJSONReadingAllowFragments error:&error];
    
    if( error != nil )
    {
        NSLog(@"Malformed Json Response, [%@] [%s]", error.localizedDescription, __FUNCTION__);
        NSLog(@"ResponseData : %@", [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding]);
        return;
    }

    NSLog(@"SSST %@", responseDictionary.description);
}

-(void)OnSendPushNotificationCompleted:(NSData*)responseData
{
    NSAssert1(responseData!=nil, @"Response Data Must not be nil, %s", __FUNCTION__);

    NSError* error=nil;
    NSDictionary* responseDictionary = [NSJSONSerialization JSONObjectWithData:responseData options:NSJSONReadingMutableLeaves|NSJSONReadingMutableContainers|NSJSONReadingAllowFragments error:&error];
    
    if( error != nil )
    {
        NSLog(@"Malformed Json Response, [%@] [%s]", error.localizedDescription, __FUNCTION__);
        NSLog(@"ResponseData : %@", [[NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding]);
        return;
    }

    NSLog(@"SSST %@", responseDictionary.description);
}

@end // NotiManagerClient


