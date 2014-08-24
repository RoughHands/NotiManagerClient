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
using namespace cocos2d;

class NotiManagerLayer : public Layer
{
protected:

public:
    NotiManagerLayer();
    virtual ~NotiManagerLayer();
    
    virtual bool                init();
    static NotiManagerLayer*          create();
    

};




#endif /* defined(__NotiManagerClient__NotiManagerLayer__) */
