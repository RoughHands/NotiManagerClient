//
//  NotiManagerClient.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#ifndef __NotiManagerClient__NotiManagerClient__
#define __NotiManagerClient__NotiManagerClient__

// Note : Read the following document
// NotiManagerClient/ReadeMe.txt

#ifdef __OBJC__
    #import <Foundation/Foundation.h>

    static NSString* DeviceInfoKey_AppName = @"AppName";
    static NSString* DeviceInfoKey_AppVersion = @"AppVersion";
    static NSString* DeviceInfoKey_DeviceToken = @"DeviceToken";
    static NSString* DeviceInfoKey_DeviceName = @"DeviceName";
    static NSString* DeviceInfoKey_DeviceModel = @"DeviceModel";
    static NSString* DeviceInfoKey_DeviceSystemVersion = @"DeviceSystemVersion";
    static NSString* DeviceInfoKey_IsPushBadgeOn = @"isPushBadgeOn";
    static NSString* DeviceInfoKey_IsPushAlertOn = @"isPushAlertOn";
    static NSString* DeviceInfoKey_IsPushSoundOn = @"isPushSoundOn";

    static NSString* URL_SendPushNotification = @"http://121.162.245.166:2967/PushNoti/SendPushNotification";
    static NSString* URL_RegisterUser = @"http://121.162.245.166:2967/PushNoti/RegisterNewUser";

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
    -(void)OnRegisterDeviceTokenError:(NSError*)error;
    -(void)OnSendPushNotificationError:(NSError*)error;
    @end // NotiRequest
#endif //__OBJC__

#ifdef __cplusplus
    #include <string>
    void RequestSendPushNotification(const std::string body, const int badge, const std::string locKey, const std::string actionLocKey="", const std::string launchImage="", const std::string sound="default", const std::string locArgs="{}");
#endif //__cplusplus




// How To Make Cretificate.pem
// http://qnibus.com/blog/how-to-make-certification-for-apns/
//  and remove pass phrase
//  openssl rsa -in key.pem -out dev_key.pem

#endif /* defined(__NotiManagerClient__NotiManagerClient__) */
