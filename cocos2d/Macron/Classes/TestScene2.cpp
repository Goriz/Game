//
//  TestScene2.cpp
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/24.
//
//

#include "TestScene2.h"
#include "TestScene.h"
#include "TapSprite.h"

USING_NS_CC;

Scene* TestScene2::createScene()
{
    Scene* scene = Scene::create();
    Layer* layer = TestScene2::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene2::init()
{
    if(!LayerGradient::initWithColor(Color4B(10, 60, 50, 255), Color4B(12, 12, 12, 255))){
        return false;
    }
    
    Size vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto cItem = MenuItemImage::create("Light_mini_On.png", "Light_mini_Off.png",
                                       CC_CALLBACK_1(TestScene2::menuCloseCallBack, this));
    cItem->setPosition(Vec2(origin.x+cItem->getContentSize().width/2, origin.y+cItem->getContentSize().height/2));
    
    auto nextSceneItem = MenuItemImage::create("float_ring2.png", "float_ring.png", CC_CALLBACK_0(TestScene2::changeScene, this));
    nextSceneItem->setPosition(Vec2(origin.x+cItem->getContentSize().width, origin.y+cItem->getContentSize().height/2));
    
    auto menu = Menu::create(cItem,nextSceneItem,NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu,5);
    
    auto backText = Label::createWithSystemFont("test", "", 30);
    backText->setContentSize(Size(40,80));
    backText->setPosition(200, 500);
    backText->setTag(22);
    this->addChild(backText,1);
    
    auto sp = TapSprite::create("board.png");
    sp->setPosition(Vec2(500, 200));
    sp->setTouchMove(true);
    this->addChild(sp,15);
    
    ////////////////////////////////////
    // ** ControlSwitch **
    // なぜかAndroidでは表示が壊れる
    //iosではバックが逆さまになる
    /////////////////////////////////
    ControlSwitch *switchControl = ControlSwitch::create(
                                                         Sprite::create("HelloWorld.png"),
                                                         Sprite::create("surf_board2.png"),
                                                         Sprite::create("surf_board4.png"),
                                                         Sprite::create("Light_mini_Off.png"),
                                                         Label::createWithSystemFont("On", "Arial_BoldMT", 16),
                                                         Label::createWithSystemFont("off", "Arial_BoldMT", 16));
    switchControl->setPosition(Vec2(vSize.width/2, vSize.height/2));
    switchControl->addTargetWithActionForControlEvents(this,
                                                       cccontrol_selector(TestScene2::switchCallBack),
                                                       Control::EventType::VALUE_CHANGED);
   // this->addChild(switchControl,0);
    
    //////////////////////////////
    //  ** slider switch **
    //////////////////////////////
    ControlSlider* slider =
            ControlSlider::create("HelloWorld.png", "surf_board2.png", "Light_mini_Off.png");
    slider->setMinimumAllowedValue(0.0f);
    slider->setMaximumAllowedValue(100.0f);
    slider->setValue(50.0f);
    slider->setPosition(Vec2(vSize.width/2.0f, 200));
    this->addChild(slider);
    
    ////////////////////////////
    //  ** edit box **
    ////////////////////////////
    EditBox* editBox = EditBox::create(Size(600, 100),Scale9Sprite::create()); //background none 気分です
    editBox->setPosition(Vec2(vSize.width-300, 150));
    editBox->setFontColor(Color3B::BLUE);
    editBox->setPlaceholderFontColor(Color3B::MAGENTA);
    editBox->setPlaceHolder("name:");
    editBox->setMaxLength(10);
    editBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    editBox->setDelegate(this);
    this->addChild(editBox);
    
    ///////////////////////////
    //  ** stretch bottuns
    ///////////////////////////
    Rect spriteRect = Rect(0, 0, 394, 157);
    Rect capIntent = Rect(40, 20, 314, 117);
    for(int i = 0;i < 5; i++){
        std::string str = "ぼたん";
        str += i;
        Label *label = Label::createWithSystemFont(str, "Arial_BoldMT", 15+i*10);
        Scale9Sprite* btSprite = Scale9Sprite::create("board.png", spriteRect, capIntent);
        ControlButton* bt = ControlButton::create(label,btSprite);
        bt->setPreferredSize(Size(100+i*100,100+i*50));
        bt->setPosition(Vec2(40 + i *150, i*150));
        //bt->setTitleLabel(label);
        this->addChild(bt);
    }
    
    return true;
}

//テキスト入力開始時
void TestScene2::editBoxEditingDidBegin(cocos2d::extension::EditBox *editBox)
{
    Label* tex = (Label*)this->getChildByTag(22);
    tex->setString("start");
}

void TestScene2::editBoxEditingDidEnd(cocos2d::extension::EditBox *editBox)
{
    Label* tex = (Label*)this->getChildByTag(22);
    tex->setString("return");
}

void TestScene2::editBoxReturn(cocos2d::extension::EditBox *editBox)
{
    Label* tex = (Label*)this->getChildByTag(22);
    tex->setString(editBox->getText());
}

void TestScene2::editBoxTextChanged(cocos2d::extension::EditBox *editBox, const std::string &text)
{
    Label* tex = (Label*)this->getChildByTag(22);
    tex->setString("入力中");
}

void TestScene2::changeScene()
{
    Scene* scene = Scene::create();
    Layer* layer = TestScene::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(TransitionSplitCols::create(2.0f, scene));
}

void TestScene2::switchCallBack(cocos2d::Ref *pSender, Control::EventType controlEvent){
    if(Control::EventType::VALUE_CHANGED == controlEvent){
        log("control");
    }
}

void TestScene2::menuCloseCallBack(cocos2d::Ref *pSnder)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button.Windows Store Apps do not implements a close button.",
               "Alert");
    return;
#endif
    
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
