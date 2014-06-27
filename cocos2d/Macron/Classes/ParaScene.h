//
//  ParaScene.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/26.
//
//

#ifndef __Macron__ParaScene__
#define __Macron__ParaScene__

#include <cocos2d.h>

//OS間で違いがある
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "extensions/cocos-ext.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos-ext.h"
#endif

USING_NS_CC_EXT;
USING_NS_CC;

class ParaScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallBack(Ref* pSnder);
    
    void update(float deltaTime);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ParaScene);
protected:
    std::unordered_map<int, Node*> _mouses;
    Scene* _scene;
};


#endif /* defined(__Macron__ParaScene__) */
