//
//  NotiManagerClient.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#ifndef __NotiManagerClient__NotiManagerClient__
#define __NotiManagerClient__NotiManagerClient__

class NotiManagerClient
{
private:
    static NotiManagerClient*   _SingletonInstance;
    
private:
    NotiManagerClient();
public:
    ~NotiManagerClient();
    
    static NotiManagerClient& GetInstance();
    
    void        RequestRegisterDeviceToken();
};

#endif /* defined(__NotiManagerClient__NotiManagerClient__) */
