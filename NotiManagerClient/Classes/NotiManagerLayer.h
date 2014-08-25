//
//  NotiManagerLayer.h
//  NotiManagerClient
//
//  Created by RoughHands_Black on 8/25/14.
//
//

#ifndef __NotiManagerClient__NotiManagerLayer__
#define __NotiManagerClient__NotiManagerLayer__

#include "cocos2d.h"
#include <extensions/GUI/CCEditBox/CCEditBox.h>
using namespace cocos2d;
using extension::EditBox;
using extension::EditBoxDelegate;
using cocos2d::IMEDelegate;
#include <extensions/GUI/CCControlExtension/CCScale9Sprite.h>
using extension::Scale9Sprite;

class NotiManagerLayer : public Layer, public EditBoxDelegate, public IMEDelegate
{
private:
    bool                        m_IsLocalizeTextMode;
    Sprite*                     m_Background;
    
    EditBox*                    m_LocKeyEditBox;
    EditBox*                    m_LocArg1EditBox;
    EditBox*                    m_LocArg2EditBox;
    EditBox*                    m_LocArg3EditBox;
    
    EditBox*                    m_BodyEditBox;
    
    EditBox*                    m_BadgeEditBox;
    EditBox*                    m_SoundEditBox;
    EditBox*                    m_LaunchImageEditBox;
    EditBox*                    m_ActionKeyEditBox;

    Menu*                       m_PushButton;
    
public:
    NotiManagerLayer();
    virtual ~NotiManagerLayer();
    
    virtual bool                        init();
    static NotiManagerLayer*            create();
    
    void                                InitializeLocalizeTextMode();
    void                                InitializeMessageMode();
    void                                ClearMode();
    
    
public:
    virtual void editBoxEditingDidBegin(EditBox* editBox) override;
    virtual void editBoxEditingDidEnd(EditBox* editBox) override;
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) override;
    virtual void editBoxReturn(EditBox* editBox) override;

//    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen) override;
    virtual void keyboardWillShow(IMEKeyboardNotificationInfo& info) override;
    virtual void keyboardWillHide(IMEKeyboardNotificationInfo& info) override;


};




#endif /* defined(__NotiManagerClient__NotiManagerLayer__) */
