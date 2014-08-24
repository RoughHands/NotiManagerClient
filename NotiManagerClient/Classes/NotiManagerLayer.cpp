//
//  NotiManagerLayer.cpp
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//

#include "cocos2d.h"
using namespace cocos2d;

#include "NotiManagerLayer.h"

#include "NotiManagerClient.h"


NotiManagerLayer::NotiManagerLayer():Layer()
{
}


NotiManagerLayer::~NotiManagerLayer()
{

}

NotiManagerLayer* NotiManagerLayer::create()
{
    NotiManagerLayer* layer = new NotiManagerLayer();
    
    if( layer && layer->init() )
    {
        layer->autorelease();
        return layer;
    }
    else
    {
        delete layer;
        return nullptr;
    }
}

bool NotiManagerLayer::init()
{
    if( Layer::init() == false )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite* background = Sprite::create("Default-568h@2x.png");
    background->retain();
    background->setAnchorPoint(Point(0.5f,0.5f));
    background->setPosition(Point(winSize.width*0.5f, winSize.height*0.5f));
    
    this->addChild(background);

    RequestSendPushNotification("BodyBody", 1, "Loc Key Loc Key", "Action Loc", "", "default");
    
    return true;
}


