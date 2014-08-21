//
//  NotiManagerClient.cpp
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#include "NotiManagerClient.h"

#include "curl.h"
#include "cURLpp.hpp"


NotiManagerClient* NotiManagerClient::_SingletonInstance = nullptr;

NotiManagerClient::NotiManagerClient()
{

}

NotiManagerClient::~NotiManagerClient()
{

}


NotiManagerClient& NotiManagerClient::GetInstance()
{
    if( _SingletonInstance == nullptr )
    {
        _SingletonInstance = new NotiManagerClient();
    }
    
    return *_SingletonInstance;
}

void NotiManagerClient::RequestRegisterDeviceToken()
{
    
}