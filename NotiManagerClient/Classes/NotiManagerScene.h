//
//  NotiManagerScene.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//

#ifndef __NotiManagerClient__NotiManagerScene__
#define __NotiManagerClient__NotiManagerScene__

#include "cocos2d.h"
#include "NotiManagerLayer.h"

using namespace cocos2d;

class NotiManagerScene : public Scene
{
private:
    NotiManagerLayer*       m_NotiManagerLayer;
public:
    NotiManagerScene();
    virtual ~NotiManagerScene();
    
    virtual bool init();
    static NotiManagerScene*   create();
    
    void update(float deltaTime);
    
public:
    NotiManagerLayer*       GetNotiManagerLayer()       {   return m_NotiManagerLayer; }
    
};


//class HelloWorld : public cocos2d::Layer
//{
//public:
//    // there's no 'id' in cpp, so we recommend returning the class instance pointer
//    static cocos2d::Scene* createScene();
//
//    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
//    virtual bool init();  
//    
//    // a selector callback
//    void menuCloseCallback(cocos2d::Ref* pSender);
//    
//    // implement the "static create()" method manually
//    CREATE_FUNC(HelloWorld);
//};


#endif /* defined(__NotiManagerClient__NotiManagerScene__) */
