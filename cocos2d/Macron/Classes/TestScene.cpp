//
//  TestScene.cpp
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/22.
//
//

#include "TestScene.h"
#include "FadeoutTouchLine.h"

USING_NS_CC; //use cocos2d namespace cocos2dのネームスペースを使うということ

Scene* TestScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = TestScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool TestScene::init()
{
    if(!LayerGradient::initWithColor(Color4B(200, 150, 150, 255), Color4B(150, 50, 50, 255),Vec2(1, 1))){
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(TestScene::menuCloseCallBack, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y+ closeItem->getContentSize().height/2));
    
    //*nomal item
    MenuItemImage* closeItem2 =MenuItemImage::create("surf_board2.png", "surf_board4.png",
                                                     CC_CALLBACK_1(TestScene::menuCloseCallBack, this));
    
    //add destination
    closeItem2->setPosition(Vec2(origin.x+closeItem2->getContentSize().width/2,
                                 origin.y+closeItem2->getContentSize().height/2));
    
    //*sprite close item
    Sprite* closeSprite1 = Sprite::create("surf_board2.png");
    Sprite* closeSprite2 = Sprite::create("surf_board2.png");
    //sprite2 change color
    closeSprite2->setColor(Color3B(102, 102, 102));
    MenuItemSprite *closeItem3 = MenuItemSprite::create(closeSprite1, closeSprite2,
                                                        CC_CALLBACK_0(TestScene::changeScene, this));
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

    
    sprites = new Vector<Sprite*>();
    Sprite::create("c-ball-ex2.png");
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey("c-ball-ex2.png");
    for(int i=0;i < 25; i++){
        int x = i%5;
        int y = i/5;
        sprites->pushBack(Sprite::createWithTexture(tex, Rect(x*96, y*96, 96, 96)));
    }
    
    
    ////////////////////////////////////////
    //sprite woker test　スプライト負荷テスト
    //** 結果的に不変 **
    //Spriteもキャッシュからtextureを生成しているから
    //android上だとテクスチャの重なりからか表示が変。
    ////////////////////////////////////////
    bool isBach = true;
    SpriteBatchNode *bach;
    if(isBach){
        bach = SpriteBatchNode::create("float_ring2.png");
        this->addChild(bach,0);
    }
    
    for(int i= 0;i < 500;i++){
        Sprite *sprite = isBach ? Sprite::createWithTexture(bach->getTexture())
                                :Sprite::create("float_ring2.png");
        float x = CCRANDOM_0_1()*visibleSize.width;
        float y = CCRANDOM_0_1()*visibleSize.height;
        sprite->setPosition(Vec2(x, y));
        bach->addChild(sprite);
        
        //random fade out
        FadeOut *fade = FadeOut::create(CCRANDOM_0_1()*10);
        sprite->runAction(fade);
    }
    
   // this->schedule(schedule_selector(TestScene::gameLogic), 0.02f);
    m_cont = 0;
    
    return true;
}

void TestScene::gameLogic(float dt){
    this->removeChildByTag(6);
    if(sprites && sprites->size() > 0){
        Sprite* mask = Sprite::create("surf_board4.png",Rect(20, 20, 80, 80));
        mask->setPosition(Vec2(40 + m_cont * 40, 250));
        Sprite* sp = sprites->at(m_cont);
        sp->setPosition(Vec2(40 + m_cont * 40, 250));
        
        ClippingNode* clip = ClippingNode::create(mask);
        clip->setAlphaThreshold(0.0f);
        clip->addChild(sp);
        clip->setTag(6);
        
        this->addChild(clip,7);
        m_cont = (m_cont + 1) % 25;
    }
}

void TestScene::changeScene(){
    sprites->clear();
    //シーンの遷移 change scene
    Scene *nextScene = Scene::create();
    auto layer = new SceneTestLayer1();
    nextScene->addChild(layer);
    layer->release();
    float duration = 1.0f;
    Scene *pScene = TransitionPageTurn::create(duration, nextScene,false);
    if(pScene){
        Director::getInstance()->replaceScene(pScene);
    }
}

void TestScene::menuCloseCallBack(cocos2d::Ref *pSnder)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button.Wondows Store Aplps do not implement a close button.",
               "Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//////////////////////////
//    Scene test
////////////////////////

SceneTestLayer1::SceneTestLayer1()
{
    //visible size
    Size size = Director::getInstance()->getVisibleSize();
    
    auto item1 = MenuItemFont::create( "Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
    auto item2 = MenuItemFont::create( "Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
    auto item3 = MenuItemFont::create( "Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));
    
    auto menu = Menu::create( item1, item2, item3, NULL );
    menu->alignItemsVertically();
    
    addChild( menu );
    
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create("HelloWorld.png");
    addChild(sprite);
    sprite->setPosition( Vec2(s.width-40, s.height/2) );
    auto rotate = RotateBy::create(2, 360);
    auto repeat = RepeatForever::create(rotate);
    sprite->runAction(repeat);
    
    //scrollview
    ScrollView* sView = ScrollView::create(size);
    sView->setContentSize(Size(1000, 1000));
    auto con = Sprite::create();
    con->setContentSize(Size(1000, 2000));
    con->setAnchorPoint(Vec2::ZERO);
    sView->setContainer(con);
    sView->setPosition(Vec2::ZERO);
    sView->setDelegate(this); //delegate
    sView->setTag(20);
   // sView->setZoomScale(0.5); ver3.1.1 stil not work
    this->addChild(sView);
    
    /*
    //画面全体にレイヤー表示
    auto allLayer = Sprite::create("f115.png");
    allLayer->setContentSize(size);
    allLayer->setPosition(Vec2(size.width/2, size.height/2));
     */
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch *touch, Event *event){
        FadeOutTouchLine::onTouchBegan(this, touch, event);
        return true;
    };
    listener->onTouchMoved = [this](Touch *touch, Event *event){
        FadeOutTouchLine::onTouchMoved(this, touch, event);
    };
    
    Director::getInstance()->getEventDispatcher()
      ->addEventListenerWithFixedPriority(listener, -100);
    
    
    schedule( schedule_selector(SceneTestLayer1::testDealloc),3.0f);
}

//scrollView did scroll
void SceneTestLayer1::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}
//scrollview
void SceneTestLayer1::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}


void SceneTestLayer1::testDealloc(float dt)
{
    flipCard();
    //CCLOG("SceneTestLayer1:testDealloc");
}

void SceneTestLayer1::onEnter()
{
    CCLOG("SceneTestLayer1#onEnter");
    Layer::onEnter();
}

void SceneTestLayer1::onEnterTransitionDidFinish()
{
    CCLOG("SceneTestLayer1#onEnterTransitionDidFinish");
    Layer::onEnterTransitionDidFinish();
}

SceneTestLayer1::~SceneTestLayer1()
{
    //NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(Ref* sender)
{
}

void SceneTestLayer1::onPushSceneTran(Ref* sender)
{
}

#define FLIP_DURATION 1.0f
#define CARD_FACE_TAG 11
#define CARD_BACK_TAG 12
bool isFace;

void SceneTestLayer1::flipCard()
{
    Size size = Director::getInstance()->getWinSize();
    
    ScrollView* sv = (ScrollView*)this->getChildByTag(20);
    
    //back of card カードの裏面
    Sprite *card = (Sprite*)sv->getContainer()->getChildByTag(CARD_FACE_TAG);
    if(!card){
        card = Sprite::create("f113.png");
        card->setPosition(Vec2(size.width/2, size.height/2+200));
        sv->addChild(card, CARD_FACE_TAG, CARD_FACE_TAG);
        card->setVisible(false);
        isFace = false;
    }
    
    //front of card カード表面
    Sprite *card2 = (Sprite*)sv->getContainer()->getChildByTag(CARD_BACK_TAG);
    if(!card2){
        card2 = Sprite::create("f115.png");
        card2->setPosition(card->getPosition());
        sv->addChild(card2,CARD_BACK_TAG,CARD_BACK_TAG);
    }
    
    Sprite *card3 = isFace ? card : card2;
    
    //flip card action めくりアクション
    OrbitCamera *turn = OrbitCamera::create(FLIP_DURATION/2.0f, 1, 0, 0.0f, 90.0f, 0, 0);
    Hide *hide = Hide::create();
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(SceneTestLayer1::flipCard2, this));
    card3->runAction(Sequence::create(turn,hide,func, NULL));
}

void SceneTestLayer1::flipCard2()
{
    ScrollView* sv = (ScrollView*)this->getChildByTag(20);
    ////////////////////////////////////////////////////////
    // ** ここ大事 **
    // ScrollViewの中にはContainerというレイヤーがおり、
    //　そこに描写している感じになっている。
    //　よってScrollViewの子要素を取りたいときは、コンテナにアクセス
    //　する必要がある。
    /////////////////////////////////////////////////////////
    Sprite *card = (Sprite*)sv->getContainer()->getChildByTag(CARD_FACE_TAG);
    Sprite *card2 = (Sprite*)sv->getContainer()->getChildByTag(CARD_BACK_TAG);
    Sprite *card3 = isFace ? card2 : card;
    
    isFace = !isFace;
    Show *show = Show::create();
    OrbitCamera *turn = OrbitCamera::create(FLIP_DURATION/2.0f, 1, 0, 270.0f, 90.0f, 0, 0);
    if(card3) card3->runAction(Sequence::create(show,turn, NULL));
}

void SceneTestLayer1::onQuit(Ref* sender)
{
    //getCocosApp()->exit();
    //CCDirector::getInstance()->poscene();
    
    //// HA HA... no more terminate on sdk v3.0
    //// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
    //if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
    //    [[UIApplication sharedApplication] performSelector:@selector(terminate)];
}
