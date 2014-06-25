//
//  TestScene2.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/24.
//
//

#ifndef __Macron__TestScene2__
#define __Macron__TestScene2__

#include <cocos2d.h>
//OS間で違いがある
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "extensions/cocos-ext.h"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos-ext.h"
#endif

USING_NS_CC_EXT;

class TestScene2 : public cocos2d::LayerGradient,public EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallBack(Ref* pSnder);
    
    void switchCallBack(Ref* pSender,Control::EventType controlEvent);
    
    void changeScene();
    
    void gameLogic(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene2);
private:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
};


#endif /* defined(__Macron__TestScene2__) */
