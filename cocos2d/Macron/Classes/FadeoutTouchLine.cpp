//
//  FadeoutTouchLine.cpp
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/26.
//
//

#include "FadeoutTouchLine.h"

const int FadeOutTouchLine::FADE_TAG = 1111111;
float FadeOutTouchLine::fade = 1.5f;
int FadeOutTouchLine::minSeg = 1;
float FadeOutTouchLine::stroke = 30;
Color3B FadeOutTouchLine::color = Color3B(255, 255, 0);
std::string FadeOutTouchLine::path = "Light_mini_On.png";

void FadeOutTouchLine::onTouchBegan(Node *node, Touch *touch, Event *event)
{
    if(node && touch && event){
        node->removeChildByTag(FadeOutTouchLine::FADE_TAG);
        MotionStreak* streak = MotionStreak::create(fade, minSeg, stroke, color, path);
        streak->setTag(FADE_TAG);
        node->addChild(streak);
        
        Vec2 point = node->convertToNodeSpace(touch->getLocation());
        streak->setPosition(point);
    }
}

void FadeOutTouchLine::onTouchMoved(cocos2d::Node *node, cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(node && touch){
        MotionStreak* streak = (MotionStreak*) node->getChildByTag(FadeOutTouchLine::FADE_TAG);
        if(streak){
            Vec2 point = node->convertToNodeSpace(touch->getLocation());
            streak->setPosition(point);
        }
    }
}