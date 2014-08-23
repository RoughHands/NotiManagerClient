//
//  NotiManagerClient.cpp
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/21/14.
//
//

#include "NotiManagerClient.h"
#include "cocos2d.h"
#include <cocos/network/HttpClient.h>
#include <cocos/network/HttpRequest.h>
#include <cocos/network/HttpResponse.h>
#include <spine/Json.h>

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

void NotiManagerClient::RequestRegisterDeviceToken(std::string deviceInfoJSON)
{
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");

    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl("http://121.162.245.166:2963/PushNoti/RegisterNewUser");
    request->setHeaders(headers);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback([](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
    {
        if (!response)
        {
            return;
        }
        
        if (0 != strlen(response->getHttpRequest()->getTag()))
        {
            cocos2d::log("%s completed", response->getHttpRequest()->getTag());
        }

        // Check the HTTP Status Code
        int statusCode = response->getResponseCode();
        char statusString[64] = {};
        sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
        cocos2d::log("response code: %d", statusCode);

        // A connection failure
        if (!response->isSucceed())
        {
            cocos2d::log("response failed");
            cocos2d::log("error buffer: %s", response->getErrorBuffer());
            cocos2d::log("body : %s", std::string(response->getResponseData()->begin(), response->getResponseData()->end()).c_str());
            return;
        }

        // The data will be placed in the buffer.
        std::vector<char> * buffer = response->getResponseData();
        char * concatenated = (char *) malloc(buffer->size() + 1);
        std::string s2(buffer->begin(), buffer->end());
        strcpy(concatenated, s2.c_str());

        // JSON Parser. Include "spine/Json.h".
        Json * json = Json_create(concatenated);
        if( json != nullptr )
        {
            // userID will be overflowed
            const int userID = Json_getInt(json, "userID", -1);
            const char * result = Json_getString(json, "result", "__NONE__");
            const char * errorCode = Json_getString(json, "errorcode", "__NONE__");
                    // View the console
            cocos2d::log("HTTP Response : userID : %d", userID);
            cocos2d::log("HTTP Response : result : %s", result);
            cocos2d::log("HTTP Response : errorCode : %s", errorCode);
        }
        else
        {
            cocos2d::log("Wrong JSON Type. Check It %s", __FUNCTION__);
        }

        // Delete the JSON object
        Json_dispose(json);
       
        // Deal
//        // dump data
//        std::vector *buffer = response->getResponseData();
//        printf("Http Test, dump data: ");
//        for (unsigned int i = 0; i < buffer->size(); i++)
//        {
//            printf("%c", (*buffer)[i]);
//        }
//        printf("\n");

    });
    
    request->setRequestData(deviceInfoJSON.data(), deviceInfoJSON.length());
    request->setHeaders(headers);
    request->setTag("POST Request");
 
    // Execute
    
    cocos2d::network::HttpClient::getInstance()->send(request);
 
    request->release();
}

void NotiManagerClient::RequestSendPushNotification(std::string notiMessagePayloadJSON)
{
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");

    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl("http://121.162.245.166:2963/PushNoti/SendPushNotification");
    request->setHeaders(headers);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback([](cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
    {
        if (!response)
        {
            return;
        }
        
        if (0 != strlen(response->getHttpRequest()->getTag()))
        {
            cocos2d::log("%s completed", response->getHttpRequest()->getTag());
        }

        // Check the HTTP Status Code
        int statusCode = response->getResponseCode();
        char statusString[64] = {};
        sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
        cocos2d::log("response code: %d", statusCode);

        // A connection failure
        if (!response->isSucceed())
        {
            cocos2d::log("response failed");
            cocos2d::log("error buffer: %s", response->getErrorBuffer());
            cocos2d::log("body : %s", std::string(response->getResponseData()->begin(), response->getResponseData()->end()).c_str());
            return;
        }

        // The data will be placed in the buffer.
        std::vector<char> * buffer = response->getResponseData();
        char * concatenated = (char *) malloc(buffer->size() + 1);
        std::string s2(buffer->begin(), buffer->end());
        strcpy(concatenated, s2.c_str());

        // JSON Parser. Include "spine/Json.h".
        Json * json = Json_create(concatenated);
        if( json != nullptr )
        {
            // userID will be overflowed
            const int numberOfUsers = Json_getInt(json, "numberOfUsers", -1);
            const char * result = Json_getString(json, "result", "__NONE__");
            const char * errorCode = Json_getString(json, "errorcode", "__NONE__");
                    // View the console
            cocos2d::log("HTTP Response : numberOfUsers : %d", numberOfUsers);
            cocos2d::log("HTTP Response : result : %s", result);
            cocos2d::log("HTTP Response : errorCode : %s", errorCode);
        }
        else
        {
            cocos2d::log("Wrong JSON Type. Check It %s", __FUNCTION__);
        }

        // Delete the JSON object
        Json_dispose(json);
       
        // Deal
//        // dump data
//        std::vector *buffer = response->getResponseData();
//        printf("Http Test, dump data: ");
//        for (unsigned int i = 0; i < buffer->size(); i++)
//        {
//            printf("%c", (*buffer)[i]);
//        }
//        printf("\n");

    });
    
    request->setRequestData(notiMessagePayloadJSON.data(), notiMessagePayloadJSON.length());
    request->setHeaders(headers);
    request->setTag("POST Request");
 
    // Execute
    
    cocos2d::network::HttpClient::getInstance()->send(request);
 
    request->release();
}