//
//  ModalLayer.h
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/26.
//
//

#ifndef __Macron__ModalLayer__
#define __Macron__ModalLayer__

#include <cocos2d.h>
USING_NS_CC;

class ModalLayer : public Layer
{
public:
    virtual bool init();
    void menuCloseCallBack(Ref* pSender);
    virtual bool onTouchBegan(Touch* touch,Event* event);
    CREATE_FUNC(ModalLayer);
};

#endif /* defined(__Macron__ModalLayer__) */
