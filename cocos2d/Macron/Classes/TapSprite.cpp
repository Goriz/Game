//
//  TapSprite.cpp
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/25.
//
//

#include "TapSprite.h"

TapSprite* TapSprite::create(const char *pszFileName)
{
    TapSprite* pobSprite = new TapSprite();
    if(pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return nullptr;
}

void TapSprite::setTouchMove(bool b){
    this->isTouchMove = b;
}

bool TapSprite::getTouchMove(){
    return isTouchMove;
}

void TapSprite::onEnter()
{
    Sprite::onEnter();
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(TapSprite::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TapSprite::onTouchMoved , this);
    listener->onTouchEnded = CC_CALLBACK_2(TapSprite::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TapSprite::onTouchCancelled, this);
    
    // add listener  リスナーの登録
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TapSprite::onExit()
{
    Sprite::onExit();
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    //remove listener リスナーの解放
    dispatcher->removeEventListenersForTarget(this);
}

bool TapSprite::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Vec2 point = touch->getLocation();
    
    Size size = this->getTexture()->getContentSize();
    
    Rect rect = Rect(this->getPositionX()-size.width/2, this->getPositionY()-size.height/2,
                     size.width, size.height);
    
    return rect.containsPoint(point);
}

void TapSprite::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
   if(isTouchMove) this->setPosition(Vec2(touch->getLocation().x, touch->getLocation().y));
}

void TapSprite::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

void TapSprite::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
}

