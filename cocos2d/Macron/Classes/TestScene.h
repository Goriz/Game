//
//  TestScene.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/22.
//
//

#ifndef __Macron__TestScene__
#define __Macron__TestScene__

#include <iostream>
#include <cocos2d.h>

class TestScene : public cocos2d::LayerGradient
{
protected:
    int m_cont;
    cocos2d::Vector<cocos2d::Sprite*> *sprites;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuCloseCallBack(Ref* pSnder);
    
    void changeScene();
    
    void gameLogic(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene);
};

class SceneTestLayer1 : public cocos2d::Layer
{
public:
    SceneTestLayer1();
    ~SceneTestLayer1();
    
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    
    void testDealloc(float dt);
    void onPushScene(Ref* sender);
    void onPushSceneTran(Ref* sender);
    void onQuit(Ref* sender);
    
    void flipCard();
    
    void flipCard2();
    
    //CREATE_NODE(SceneTestLayer1);
} ;

#endif /* defined(__Macron__TestScene__) */
