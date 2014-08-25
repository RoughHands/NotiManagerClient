//
//  NotiManagerLayer.cpp
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//

#include "Prefix.pch"

#include <CCEventListenerTouch.h>

#include "NotiManagerLayer.h"
#include "NotiManagerClient.h"

using namespace cocos2d;
using extension::EditBox;
using extension::EditBoxDelegate;
using cocos2d::IMEDelegate;
using extension::Scale9Sprite;



NotiManagerLayer::NotiManagerLayer():Layer(),
                            m_IsLocalizeTextMode(false),
                            m_Background(nullptr),
                            m_LocKeyEditBox(nullptr),
                            m_LocArg1EditBox(nullptr),
                            m_LocArg2EditBox(nullptr),
                            m_LocArg3EditBox(nullptr),
                            m_BodyEditBox(nullptr),
                            m_BadgeEditBox(nullptr),
                            m_SoundEditBox(nullptr),
                            m_LaunchImageEditBox(nullptr),
                            m_ActionKeyEditBox(nullptr),
                            m_PushButton(nullptr)
{
}


#define RemoveAndReleaseNode(NodePointer) \
    if( NodePointer != nullptr )\
    {\
        NodePointer->stopAllActions();\
        NodePointer->removeFromParent();\
        NodePointer->release();\
        NodePointer = nullptr;\
    }


NotiManagerLayer::~NotiManagerLayer()
{
    RemoveAndReleaseNode(m_Background);
    RemoveAndReleaseNode(m_LocKeyEditBox);
    RemoveAndReleaseNode(m_LocArg1EditBox);
    RemoveAndReleaseNode(m_LocArg2EditBox);
    RemoveAndReleaseNode(m_LocArg3EditBox);
    RemoveAndReleaseNode(m_BodyEditBox);
    RemoveAndReleaseNode(m_BadgeEditBox);
    RemoveAndReleaseNode(m_SoundEditBox);
    RemoveAndReleaseNode(m_LaunchImageEditBox);
    RemoveAndReleaseNode(m_ActionKeyEditBox);
    RemoveAndReleaseNode(m_PushButton);
    
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

void NotiManagerLayer::InitializeLocalizeTextMode()
{
    this->ClearMode();
    
    const Size winSize = Director::getInstance()->getWinSize();
    Size textFieldSize = Size(winSize.width*0.8f, 50.f);
    float heightOffset = -200.f;
    {
        // Loc Key EditBox
        Scale9Sprite* keyEditBoxSprite = Scale9Sprite::create("editbox.png");
        keyEditBoxSprite->setOpacity(223);
        m_LocKeyEditBox = EditBox::create(textFieldSize, keyEditBoxSprite);
        m_LocKeyEditBox->setColor(Color3B::BLACK);
        m_LocKeyEditBox->retain();
        m_LocKeyEditBox->setPosition(Point(winSize.width*0.5f, winSize.height+heightOffset));
        m_LocKeyEditBox->setFontColor(Color3B::WHITE);
        m_LocKeyEditBox->setPlaceHolder("Localize Key");
        m_LocKeyEditBox->setMaxLength(80);
        m_LocKeyEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_LocKeyEditBox->setDelegate(this);
        this->addChild(m_LocKeyEditBox);
    }
    
    const Size locArgFieldSize(winSize.width*0.6f, 50.f);
    {
        // Loc Arg1 EditBox
        Scale9Sprite* locArg1BoxSprite = Scale9Sprite::create("editbox.png");
        locArg1BoxSprite->setOpacity(223);
        m_LocArg1EditBox = EditBox::create(locArgFieldSize, locArg1BoxSprite);
        m_LocArg1EditBox->setColor(Color3B::WHITE);
        m_LocArg1EditBox->retain();
        heightOffset -= 85.f;
        m_LocArg1EditBox->setPosition(Point(winSize.width*0.6f, winSize.height+heightOffset));
        m_LocArg1EditBox->setFontColor(Color3B::BLACK);
        m_LocArg1EditBox->setPlaceHolder("Localize Arg Key");
        m_LocArg1EditBox->setMaxLength(80);
        m_LocArg1EditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_LocArg1EditBox->setDelegate(this);
        this->addChild(m_LocArg1EditBox);
    }
    
    {
        // Loc Arg2 EditBox
        Scale9Sprite* locArg2BoxSprite = Scale9Sprite::create("editbox.png");
        locArg2BoxSprite->setOpacity(223);
        m_LocArg2EditBox = EditBox::create(locArgFieldSize, locArg2BoxSprite);
        m_LocArg2EditBox->setColor(Color3B::WHITE);
        m_LocArg2EditBox->retain();
        heightOffset -= 85.f;
        m_LocArg2EditBox->setPosition(Point(winSize.width*0.6f, winSize.height+heightOffset));
        m_LocArg2EditBox->setFontColor(Color3B::BLACK);
        m_LocArg2EditBox->setPlaceHolder("Localize Arg Key");
        m_LocArg2EditBox->setMaxLength(80);
        m_LocArg2EditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_LocArg2EditBox->setDelegate(this);
        this->addChild(m_LocArg2EditBox);
    }

    {
        // Loc Arg3 EditBox
        Scale9Sprite* locArg3BoxSprite = Scale9Sprite::create("editbox.png");
        locArg3BoxSprite->setOpacity(223);
        m_LocArg3EditBox = EditBox::create(locArgFieldSize, locArg3BoxSprite);
        m_LocArg3EditBox->setColor(Color3B::WHITE);
        m_LocArg3EditBox->retain();
        heightOffset -= 85.f;
        m_LocArg3EditBox->setPosition(Point(winSize.width*0.6f, winSize.height+heightOffset));
        m_LocArg3EditBox->setFontColor(Color3B::BLACK);
        m_LocArg3EditBox->setPlaceHolder("Localize Arg Key");
        m_LocArg3EditBox->setMaxLength(80);
        m_LocArg3EditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_LocArg3EditBox->setDelegate(this);
    
        this->addChild(m_LocArg3EditBox);
    }
}

void NotiManagerLayer::InitializeMessageMode()
{
    this->ClearMode();
    
    const Size winSize = Director::getInstance()->getWinSize();
    Size textFieldSize = Size(winSize.width*0.8f, 50.f);
    float heightOffset = -200.f;
    {
        // Body EditBox
        Scale9Sprite* locArg3BoxSprite = Scale9Sprite::create("editbox.png");
        locArg3BoxSprite->setOpacity(223);
        m_BodyEditBox = EditBox::create(textFieldSize, locArg3BoxSprite);
        m_BodyEditBox->setColor(Color3B::BLACK);
        m_BodyEditBox->retain();
        heightOffset -= 85.f;
        m_BodyEditBox->setPosition(Point(winSize.width*0.5f, winSize.height+heightOffset));
        m_BodyEditBox->setFontColor(Color3B::WHITE);
        m_BodyEditBox->setPlaceHolder("            Notification Message");
        m_BodyEditBox->setMaxLength(80);
        m_BodyEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_BodyEditBox->setDelegate(this);
    
        this->addChild(m_BodyEditBox);
        
        
        m_BodyEditBox->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.15f, Point(0.f,20.f)),MoveBy::create(1.15f,Point(0.f,-20.f)), NULL)));
    }
    
}

void NotiManagerLayer::ClearMode()
{
    RemoveAndReleaseNode(m_BodyEditBox);
    RemoveAndReleaseNode(m_LocKeyEditBox);
    RemoveAndReleaseNode(m_LocArg1EditBox);
    RemoveAndReleaseNode(m_LocArg2EditBox);
    RemoveAndReleaseNode(m_LocArg3EditBox);
}

bool NotiManagerLayer::init()
{
    if( Layer::init() == false )
    {
        return false;
    }
    
    m_IsLocalizeTextMode = false;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    m_Background = Sprite::create("notiman_background.png");
    m_Background->retain();
    m_Background->setAnchorPoint(Point(0.5f,0.5f));
    m_Background->setPosition(Point(winSize.width*0.5f, winSize.height*0.5f));
    
    this->addChild(m_Background);


    if( m_IsLocalizeTextMode == false )
    {
        this->InitializeMessageMode();
    }
    else
    {
        this->InitializeLocalizeTextMode();
    }
    
    // Badge
    // Sound
    // ActionKey
    float heightOffset = -450.f;
    {
        // Badge EditBox
        Size badgeFieldSize = Size(200.f, 50.f);
        Scale9Sprite* locArg3BoxSprite = Scale9Sprite::create("editbox.png");
        locArg3BoxSprite->setOpacity(223); 
        m_BadgeEditBox = EditBox::create(badgeFieldSize, locArg3BoxSprite);
        m_BadgeEditBox->setColor(Color3B::BLACK);
        m_BadgeEditBox->retain();
        m_BadgeEditBox->setPosition(Point(winSize.width*0.5f, winSize.height+heightOffset));
        m_BadgeEditBox->setFontColor(Color3B::WHITE);
        m_BadgeEditBox->setPlaceHolder("     Badge");
        m_BadgeEditBox->setMaxLength(3);
        m_BadgeEditBox->setInputMode(EditBox::InputMode::NUMERIC);
        m_BadgeEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_BadgeEditBox->setDelegate(this);
    
        this->addChild(m_BadgeEditBox);
    }
    
    heightOffset -= 80.f;
    {
        // Sound EditBox
        Size soundFieldSize = Size(200.f, 50.f);
        Scale9Sprite* locArg3BoxSprite = Scale9Sprite::create("editbox.png");
        locArg3BoxSprite->setOpacity(223); 
        m_SoundEditBox = EditBox::create(soundFieldSize, locArg3BoxSprite);
        m_SoundEditBox->setColor(Color3B::BLACK);
        m_SoundEditBox->retain();
        m_SoundEditBox->setPosition(Point(winSize.width*0.5f, winSize.height+heightOffset));
        m_SoundEditBox->setFontColor(Color3B::WHITE);
        m_SoundEditBox->setPlaceHolder("     Sound");
        m_SoundEditBox->setMaxLength(3);
        m_SoundEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_SoundEditBox->setDelegate(this);
    
        this->addChild(m_SoundEditBox);
    }
    
    heightOffset -= 80.f;
    {
        // LaunchImage EditBox
        Size launchImageFieldSize = Size(250.f, 50.f);
        Scale9Sprite* locArg3BoxSprite = Scale9Sprite::create("editbox.png");
        locArg3BoxSprite->setOpacity(223); 
        m_LaunchImageEditBox = EditBox::create(launchImageFieldSize, locArg3BoxSprite);
        m_LaunchImageEditBox->setColor(Color3B::BLACK);
        m_LaunchImageEditBox->retain();
        m_LaunchImageEditBox->setPosition(Point(winSize.width*0.5f, winSize.height+heightOffset));
        m_LaunchImageEditBox->setFontColor(Color3B::WHITE);
        m_LaunchImageEditBox->setPlaceHolder("  LaunchImage");
        m_LaunchImageEditBox->setMaxLength(3);
        m_LaunchImageEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
        m_LaunchImageEditBox->setDelegate(this);
    
        this->addChild(m_LaunchImageEditBox);
    }
    
    {
        Label* pushLabel = Label::createWithTTF("PUSH!", "fonts/Marker Felt.ttf", 80.f);
        pushLabel->setColor(Color3B::RED);
        MenuItemLabel* pushMenuItem = MenuItemLabel::create(pushLabel, [this](Ref*)
                {
                    EditBox* editBox = this->m_IsLocalizeTextMode==true? m_LocKeyEditBox:m_BodyEditBox;
            
                    std::string message = editBox->getText();
                    if( message.length() <= 0 )
                    {
                        std::vector<std::string> messageList;
                        messageList.push_back("Continue to Play! 고고?");
                        messageList.push_back("What are you waiting for? 고고!");
                        messageList.push_back("What? 뭐함?!");
                        messageList.push_back("^*^ 아잉!");
                        messageList.push_back("Na Ni El Ba Bo");
                        int randomIndex = std::rand()%messageList.size();
                        
                        message = messageList[randomIndex];
                    }
                    
                    editBox->setText("");
                    
                    std::string badge = this->m_BadgeEditBox->getText();
                    int badgeNumber = badge.length()>0? atoi(this->m_BadgeEditBox->getText()):1;
                    
                    std::string sound = this->m_SoundEditBox->getText();
                    if( sound.length() <= 0 )
                    {
                        sound = "default";
                    }
                    
                    std::string launchImage = this->m_LaunchImageEditBox->getText();
                    
                    if( m_IsLocalizeTextMode == true )
                    {
                        RequestSendPushNotification("", badgeNumber, message, "Action Loc", launchImage, sound);
                    }
                    else
                    {
                        RequestSendPushNotification(message, badgeNumber, "", "", launchImage, sound);
                    }
                });
        pushMenuItem->setAnchorPoint(Point(0.5f,0.5f));
        pushMenuItem->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.15f, 1.3f),ScaleTo::create(0.1f, 1.f),
                                                                    ScaleTo::create(0.15f,1.4f),ScaleTo::create(0.1f,1.f), DelayTime::create(2.f),  NULL)));
        m_PushButton = Menu::createWithItem(pushMenuItem);
        m_PushButton->retain();
        m_PushButton->setAnchorPoint(Point(0.5f,0.5f));
        
        m_PushButton->setPosition(Point(winSize.width+300.f, 350.f));
        
        m_PushButton->runAction(RepeatForever::create(Sequence::create(MoveTo::create(2.f, Point(-300.f, 350.f)), MoveTo::create(0.f, Point(winSize.width+300.f,350.f)), NULL)));
        this->addChild(m_PushButton);
    }

    return true;
}

void NotiManagerLayer::editBoxEditingDidBegin(EditBox* editBox)
{
    Size uiLayerSize = this->getContentSize();
    

}

void NotiManagerLayer::editBoxEditingDidEnd(EditBox* editBox)
{

}

void NotiManagerLayer::editBoxTextChanged(EditBox* editBox, const std::string& text)
{

}

void NotiManagerLayer::editBoxReturn(EditBox* editBox)
{

}


void NotiManagerLayer::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
}

void NotiManagerLayer::keyboardWillHide(IMEKeyboardNotificationInfo& info)
{
}

