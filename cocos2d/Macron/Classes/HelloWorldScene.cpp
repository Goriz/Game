#include "HelloWorldScene.h"
#include "TestScene2.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first with gradation
    if ( !LayerGradient::initWithColor(Color4B(70, 145, 15, 255),Color4B(170, 220, 120, 255),Vec2(0,1)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    //** menu button added **//
    
    //*nomal item
    MenuItemImage* closeItem2 =MenuItemImage::create("surf_board2.png", "surf_board4.png",
                                                     CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    //add destination
    closeItem2->setPosition(Vec2(origin.x+closeItem2->getContentSize().width/2,
                                 origin.y+closeItem2->getContentSize().height/2));
    
    //*sprite close item
    Sprite* closeSprite1 = Sprite::create("surf_board2.png");
    Sprite* closeSprite2 = Sprite::create("surf_board2.png");
    //sprite2 change color
    closeSprite2->setColor(Color3B(102, 102, 102));
    MenuItemSprite *closeItem3 = MenuItemSprite::create(closeSprite1, closeSprite2,
                                                        CC_CALLBACK_0(HelloWorld::changeScene, this));
    //set distination
    closeItem3->setPosition(closeItem2->getPositionX()+closeItem2->getContentSize().width,
                            closeItem2->getPositionY());
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    //add menu
    menu->addChild(closeItem2,1);
    menu->addChild(closeItem3,1);
    
    //** toggle button set **//
    //off toggle
    Sprite* tgOffSp1 = Sprite::create("Light_mini_Off.png");
    Sprite* tgOffSp2 = Sprite::create("Light_mini_Off.png");
    //color change
    tgOffSp2->setColor(Color3B(102, 102, 102));
    //create manu sprite
    MenuItemSprite* tgOffItem = MenuItemSprite::create(tgOffSp1, tgOffSp2,nullptr);
    
    //on toggle
    Sprite* tgOnSp1 = Sprite::create("Light_mini_On.png");
    Sprite* tgOnSp2 = Sprite::create("Light_mini_On.png");
    //color change
    tgOnSp2->setColor(Color3B(102, 102, 102));
    //create manu sprite
    MenuItemSprite* tgOnItem = MenuItemSprite::create(tgOnSp1, tgOnSp2,nullptr);
    
    //create toggle button
    MenuItemToggle* toggleItem =
    MenuItemToggle::createWithCallback(CC_CALLBACK_1(HelloWorld::changeMode, this),
                                       tgOffItem,tgOnItem, NULL);
    
    //set position
    toggleItem->setPosition(Vec2(origin.x+toggleItem->getContentSize().width/2,
                                 origin.y+visibleSize.height-toggleItem->getContentSize().height/2));
    //set index
    toggleItem->setSelectedIndex(1);
    
    //create togglMenu
    Menu *tMenu = Menu::create(toggleItem, NULL);
    tMenu->setPosition(Vec2::ZERO);
    tMenu->setTag(3);
    //add layer
    this->addChild(tMenu);
    
    //** score text **//
    auto *scoreLabel = LabelTTF::create("Score", "arial", 48);
    scoreLabel->setPosition(Vec2(origin.x+visibleSize.width/2-scoreLabel->getContentSize().width/2,
                                 origin.y + visibleSize.height-scoreLabel->getContentSize().height/2));
    scoreLabel->setTag(10);
    this->addChild(scoreLabel,5);
    //score point
    auto *scorePoint = LabelTTF::create("0", "arial", 48);
    scorePoint->setPosition(Vec2(scoreLabel->getPositionX()+scoreLabel->getContentSize().width,
                                 scoreLabel->getPositionY()));
    scorePoint->setTag(11);
    this->addChild(scorePoint,5);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add "HelloWorld" splash screen"
    Sprite *sprite = Sprite::create("body_set.png",Rect(0, 0, 256, 256));
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    //set Tag
    sprite->setTag(1);
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic),3.0f);
    
    //set multi touch mode
    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    
    //set touch enable ok
    //this->setTouchEnabled(true); **not need,because do that method in setTouchMode.
    
    //registration multi touch event!
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //update on
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::changeScene(){
    //シーンの遷移 change scene a
    auto *nextScene = TestScene2::createScene();
    float duration = 1.0f;
    Scene *pScene = TransitionPageTurn::create(duration, nextScene,false);
    if(pScene){
        Director::getInstance()->replaceScene(pScene);
    }
}

//update
void HelloWorld::update(float dt){
    //get sprite
    Sprite* player = (Sprite*)this->getChildByTag(1);
    
    //rect colision
    Rect playerRect = Rect(player->getPositionX() - (player->getContentSize().width/4),
                           player->getPositionY() - (player->getContentSize().height/4),
                           player->getContentSize().width/2, player->getContentSize().height/2);
    
    //get ring sprite
    Sprite* food = (Sprite*)this->getChildByTag(2);
    if(food == nullptr) return;
    
    //set food rect
    Rect foodRect = Rect(food->getPositionX() - (food->getContentSize().width/2),
                         food->getPositionY() - (food->getContentSize().height/2),
                         food->getContentSize().width, food->getContentSize().height);
    
    //check colision
    if(playerRect.intersectsRect(foodRect) && player->isVisible()){
        this->removeChild(food,true);
        
        //change texture player
        player->setTextureRect(Rect(256, 0, 256, 256));
        
        //once call 'eat' method
        this->scheduleOnce(schedule_selector(HelloWorld::eat), 0.1f);
        
    }
    
}

//cahnge mode
void HelloWorld::changeMode(cocos2d::Ref *pSender){
    //get index
    int selectIndex = dynamic_cast<MenuItemToggle*>(pSender)->getSelectedIndex();
    
    Sprite* player = (Sprite*)this->getChildByTag(1);
    //toggle on -> visible true,toggle -> visible false
    player->setVisible(selectIndex);
}

void HelloWorld::eat(float dt){
    log("dt : %f",dt);
    //get player
    Sprite* player = (Sprite*)this->getChildByTag(1);
    
    player->setTextureRect(Rect(0, 0, 256, 256));
    
    //plus score points
    Size winSize = Director::getInstance()->getWinSize();
    this->m_points += player->getPositionX()/(winSize.width/4) + 1;
    //get score label
    auto pointLabel = (LabelTTF*)this->getChildByTag(11);
    auto *points = String::createWithFormat("%d",m_points);
    pointLabel->setString(points->getCString());
    
    //add frame animations フレームアニメーションを追加したよ
    Animation *frameAnime = Animation::create();
    
    const int frameNum = 5;
    Sprite *animSprite = Sprite::create("c-ball-ex2.png");
    //ここで一度スプライトとして登録したので、キャッシュされているテクスチャを取り出す。
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey("c-ball-ex2.png");
    for(int i = 0;i < frameNum;i++){
        //clip the player texture for frame animation. 画像から矩形を選択してフレームとして切り抜く
        frameAnime->addSpriteFrameWithTexture(tex, Rect(i*96, 0, 96, 96));
    }
    //300msec/5frame
    frameAnime->setDelayPerUnit(0.3f/5.0f);
    //loop 3times. それを繰り返すこともできる
    frameAnime->setLoops(3);
    //If animation finished,set original image. アニメーション終了後、もとに戻す
    frameAnime->setRestoreOriginalFrame(true);
    
    //do animation. アニメーションの実行
    Animate *action = Animate::create(frameAnime);
    player->runAction(action);
}

//touch began multi
void HelloWorld::onTouchesBegan	(const std::vector<cocos2d::Touch * >& touches,cocos2d::Event* event){
    for (auto touch1 : touches) {
        if(touch1 != nullptr){
            Touch *touch = (Touch*)touch1;
            Point location = touch->getLocationInView();
            location = Director::getInstance()->convertToGL(location);
            
            //get macron (tag = 1)
            Sprite *player = (Sprite*)this->getChildByTag(1);
            player->stopActionByTag(5);
            
            //window size
            Size winSize = Director::getInstance()->getWinSize();
            
            //length for duration
            float length = sqrtf(powf(location.x - player->getPositionX(), 2.0f)+
                                 powf(location.y - player->getPositionY(),2.0f));
            
            float duration = length / winSize.width * 1.5f;
            MoveTo* actionMove = MoveTo::create(duration, location);
            actionMove->setTag(5);
            player->runAction(actionMove);
            
        }
    }
}


void HelloWorld::gameLogic(float delta){
    this->addFood();
}

void HelloWorld::addFood(){
    Size winSize = Director::getInstance()->getWinSize();
    Sprite *food = Sprite::create("float_ring.png");
    int height = rand() % (int)winSize.height;
    food->setPosition(winSize.width + food->getContentSize().width/2,height);
    food->setTag(2);
    this->addChild(food,2);
    
    //2seconds wait
    float duration = 2.0f;
    
    //create action
    MoveTo *actionMove =
    MoveTo::create(duration, Point(-food->getContentSize().width/2,food->getPositionY()));
    
    //finish action
    CallFuncN* actionMoveDone =
       CallFuncN::create([this](Node * sender){
        this->spriteMoveFinished(sender);
        });
    
    food->runAction(Sequence::create(actionMove,actionMoveDone,NULL));
    
    //** add more action! **//
    
    ActionInterval *action1;
    ActionInterval *action2;
    
    //for bazie curve
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Vec2(winSize.width, winSize.height);
    bezier.controlPoint_2 = Vec2(winSize.width/2, -winSize.height);
    bezier.endPosition = Vec2(0, winSize.height);
    
    //switch action
    switch (this->m_actionType) {
        case 1:
            //expansion
            action1 = ScaleTo::create(duration, 4.0f); //scale to 4 times!
            food->runAction(action1);
            break;
        case 2:
            //rotation 360'
            action1 = RotateBy::create(duration, 360);
            food->runAction(action1);
            break;
        case 3:
            //expand and rotate
            action1 = ScaleTo::create(duration, 4.0f);
            action2 = RotateBy::create(duration, 360);
            food->runAction(action1);
            food->runAction(action2);
            break;
        case 4:
            //foever repeat
            action1 = RotateBy::create(0.5f, 360);
            action2 = RepeatForever::create(action1);
            food->runAction(action2);
            break;
        case 5:
            //jump:height 100,times 5
            action1 = JumpBy::create(duration, Vec2(0, 0), 100, 5);
            food->runAction(action1);
            break;
        case 6:
            //4 times scaling and 3times jump!
            action1 = ScaleTo::create(duration/2, 4.0f);
            action2 = JumpBy::create(duration/2, Vec2(0, 0), 100, 3);
            food->runAction(Sequence::create(action1,action2, NULL));
            break;
        case 7:
            //fade out,fade in
            //hirf time fade in
            action1 = FadeIn::create(duration/2.0f);
            //fade out (riverse)
            action2 = action1->reverse();
            food->runAction(Sequence::create(action1,action2,NULL));
            break;
        case 8:
            //horizontal move stop
            food->stopAllActions();
            //start bezie move
            action1 = BezierTo::create(duration, bezier);
            food->runAction(Sequence::create(action1,actionMoveDone, NULL));
            break;
        case 9:
            //horizontal move stop
            food->stopAllActions();
            //ease int out add
            action1 = EaseInOut::create(actionMove, 3.0f);
            food->runAction(Sequence::create(action1,actionMoveDone,NULL));
            break;
        case 10:
            //horizontal move stop
            food->stopAllActions();
            //ease bounce move add
            action1 = EaseBounceOut::create(actionMove);
            food->runAction(Sequence::create(action1,actionMove, NULL));
            break;
        case 11:
            //horizontal move stop
            food->stopAllActions();
            //bounce horizontal last
            action1 = EaseBounceOut::create(actionMove);
            food->runAction(action1);
            //jump action add
            action2 = JumpBy::create(duration, Vec2(0, 0), 100, 5);
            food->runAction(action2);
            break;
        default:
            //horizontal move
            break;
    }
    //icrement type
    this->m_actionType = (m_actionType+1)%12;
}

void HelloWorld::spriteMoveFinished(cocos2d::Node *sender){
    Sprite* sprite = (Sprite*)sender;
    bool isCleanUp = true;
    this->removeChild(sprite,isCleanUp);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
