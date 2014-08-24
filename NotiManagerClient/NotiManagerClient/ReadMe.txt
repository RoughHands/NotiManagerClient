//
//  ReadMe.txt
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//


1) How To Make Cretificate.pem

http://qnibus.com/blog/how-to-make-certification-for-apns/

remove pass phrase
openssl rsa -in key.pem -out dev_key.pem


2) To Do 1 :
  On AppCotroller, add below codes

    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions )
    {
        ...
        ...
        [[NotiManagerClient getInstance] InitializeService:application];
        return YES;
    }

3) To Do 2: override this function on AppController
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    #if !TARGET_IPHONE_SIMULATOR
    
    [[NotiManagerClient getInstance] RequestRegisterDeviceToken:deviceToken];
    
    [[NotiManagerClient getInstance] RequestSendPushNotification:@"Body11" badge:2 locKey:@"Loc Key" lokArgs:@"{}" actionLocKey:@"Loc Key" launchImage:@"" sound:@"default"];
    #endif
}


#endif
