//
//  NotiManagerLayer.cpp
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//

#include <CCEventListenerTouch.h>

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
    
    Sprite* background = Sprite::create("notiman_background.png");
    background->retain();
    background->setAnchorPoint(Point(0.5f,0.5f));
    background->setPosition(Point(winSize.width*0.5f, winSize.height*0.5f));
    
    this->addChild(background);

    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event)->bool
    {
        std::vector<std::string> locKeyList;
        locKeyList.push_back("Continue to Play! 고고?");
        locKeyList.push_back("What are you waiting for? 고고!");
        locKeyList.push_back("What? 뭐함?!");
        locKeyList.push_back("^*^ 아잉!");
        
        int randomIndex = std::rand()%locKeyList.size();

        RequestSendPushNotification("BodyBody", 1, locKeyList[randomIndex], "Action Loc", "", "default");
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


