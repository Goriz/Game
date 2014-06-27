//
//  FadeoutTouchLine.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/26.
//
//

#ifndef __Macron__FadeoutTouchLine__
#define __Macron__FadeoutTouchLine__

#include <cocos2d.h>
USING_NS_CC;

class FadeOutTouchLine
{
private:
    static const int FADE_TAG;
    static float fade;
    static int minSeg;
    static float stroke;
    static Color3B color;
    static std::string path;
    
public:
    static void onTouchBegan(Node* node,Touch* touch,Event* event);
    
    static void onTouchMoved(Node* node,Touch* touch,Event* event);
};
#endif /* defined(__Macron__FadeoutTouchLine__) */
