//
//  TapSprite.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/25.
//
//

#ifndef __Macron__TapSprite__
#define __Macron__TapSprite__

#include <cocos2d.h>
//OS間で違いがある
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "extensions/cocos-ext.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos-ext.h"
#endif

USING_NS_CC_EXT;
USING_NS_CC;

class TapSprite : public Sprite
{
private:
    bool isTouchMove = false;
    
public:
    static TapSprite* create(const char *pszFileName);
    
    void setTouchMove(bool b);
    
    bool getTouchMove();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    
    virtual void onTouchMoved(Touch* touch, Event* event);
    
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    virtual void onTouchCancelled(Touch* touch, Event* event);
};

#endif /* defined(__Macron__TapSprite__) */
