////
////  NotiManagerScene.cpp
////  NotiManagerClient
////
////  Created by RoughHands_Black on 8/25/14.
////
////
//
#include "NotiManagerScene.h"

USING_NS_CC;

NotiManagerScene::NotiManagerScene():Scene(),m_NotiManagerLayer(nullptr)
{
}

NotiManagerScene::~NotiManagerScene()
{

}

bool NotiManagerScene::init()
{
    if( Scene::init() == false )
    {
        return false;
    }
    
    m_NotiManagerLayer = NotiManagerLayer::create();
    m_NotiManagerLayer->retain();
    
    this->addChild(m_NotiManagerLayer);
    
    return true;
}


NotiManagerScene* NotiManagerScene::create()
{
    NotiManagerScene* scene = new NotiManagerScene();
    if( scene && scene->init() )
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}


void NotiManagerScene::update(float deltaTime)
{
    Scene::update(deltaTime);
    
}
