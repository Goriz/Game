//
//  ParaScene.cpp
//  Macron
//
//  Created by Kodai Tomoto on 2014/06/26.
//
//

#include "ParaScene.h"
#include "TapSprite.h"


Scene* ParaScene::createScene()
{
    Scene* scene = Scene::createWithPhysics();
    Vect gravity;
    gravity.setPoint(0, -50);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSpeed(6.0f);
    
    Layer* layer = ParaScene::create();
    scene->addChild(layer);
    return scene;
}

bool ParaScene::init()
{
    if(!Layer::init()){
        return false;
    }
    
    Size vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto cItem = MenuItemImage::create("Light_mini_On.png", "Light_mini_Off.png",
                                       CC_CALLBACK_1(ParaScene::menuCloseCallBack, this));
    cItem->setPosition(Vec2(origin.x+cItem->getContentSize().width/2, origin.y+cItem->getContentSize().height/2));
    
    auto menu = Menu::create(cItem,NULL);
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu,1);
    
    //parallaxNode
    
    Sprite* sp1 = Sprite::create("pipo-battlebg001.jpg");
    Sprite* sp2 = Sprite::create("pipo-battlebg001a.jpg");
    Sprite* sp3 = Sprite::create("pipo-battlebg002.jpg");
    Sprite* sp4 = Sprite::create("pipo-battlebg002a.jpg");
    
    ParallaxNode* pNode = ParallaxNode::create();
    pNode->addChild(sp1, 1, Vec2(0.0f, 0), Vec2(vSize.width/2, vSize.height/2));
    pNode->addChild(sp2, 2, Vec2(0.5f, 0), Vec2(vSize.width/2, vSize.height/4));
    pNode->addChild(sp3, 3, Vec2(1.0f, 0), Vec2(vSize.width/2, vSize.height/8));
    pNode->addChild(sp4, 4, Vec2(1.5f, 0), Vec2(vSize.width/2, -vSize.height/32));
    
    auto back = Layer::create();
    
    back->addChild(pNode);
    
    MoveTo* m1 = MoveTo::create(5.0f, Vec2(-vSize.width/3, 0));
    MoveTo* m2 = MoveTo::create(5.0f, Vec2(vSize.width/3, 0));
    Sequence* seq = Sequence::create(m1,m2, NULL);
    RepeatForever* rp = RepeatForever::create(seq);
    
    back->runAction(rp);
    this->addChild(back,0);
    
    //time progress bar
    Sprite* tSp = Sprite::create("Light_mini_On.png");
    ProgressTimer* pTimer = ProgressTimer::create(tSp);
    pTimer->setType(ProgressTimer::Type::RADIAL); //watch type
    pTimer->setPosition(Vec2(vSize.width/2, vSize.height/2));
    pTimer->setPercentage(0.0f);
    pTimer->setTag(1);
    pTimer->setPhysicsBody(PhysicsBody::createCircle(tSp->getContentSize().width/2-5));
    this->addChild(pTimer,5);
    
    this->scheduleUpdate();
    
    
    auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 50), Vec2(800, 50)));
    this->addChild(node,50);
    auto node1 = Node::create();
    node1->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 50), Vec2(0, 480)));
    this->addChild(node1,50);
    auto node2 = Node::create();
    node2->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(800, 0), Vec2(800, 480)));
    this->addChild(node2,50);
    auto node3 = Node::create();
    node3->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 480), Vec2(800,480)));
    this->addChild(node3,50);
    
    auto player = Sprite::create("title2.png");
    auto pb = PhysicsBody::createBox(Size(player->getContentSize()));
    pb->setEnable(true);
    pb->setRotationEnable(true);
    pb->setTag(55);
    player->setPosition(Vec2(220, 400));
    player->setPhysicsBody(pb);
    
    this->addChild(player,50,1);
    
    auto fem = Scale9Sprite::create("f113f.png");
    fem->setScale(0.4f);
    fem->setPhysicsBody(PhysicsBody::createBox(Size(fem->getContentSize().width*0.35f,
                                                    fem->getContentSize().height*0.35f)));
    fem->setPosition(Vec2(400, 200));
    fem->getPhysicsBody()->setTag(55);
    this->addChild(fem);
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(ParaScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(ParaScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(ParaScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}


bool ParaScene::onTouchBegan(Touch* touch, Event* event)
{
    if(!_scene) {
        _scene = dynamic_cast<Scene*>(this->getParent());
    }
    
    auto location = touch->getLocation();
    auto arr = _scene->getPhysicsWorld()->getShapes(location);
    
    PhysicsBody* body = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & 55) != 0)
        {
            body = obj->getBody();
            break;
        }
    }
    
    CCLOG("tx:%f ty:%f",location.x,location.y);
    
    Sprite* b = (Sprite*)this->getChildByTag(1);
    if(b) CCLOG("x:%f y:%f",b->getPosition().x,b->getPosition().y);
        
    if (body != nullptr)
    {
        Node* mouse = Node::create();
        mouse->setPhysicsBody(PhysicsBody::create(PHYSICS_INFINITY, PHYSICS_INFINITY));
        mouse->getPhysicsBody()->setDynamic(false);
        mouse->setPosition(location);
        this->addChild(mouse);
        PhysicsJointPin* joint = PhysicsJointPin::construct(mouse->getPhysicsBody(), body, location);
        joint->setMaxForce(5000.0f * body->getMass());
        _scene->getPhysicsWorld()->addJoint(joint);
        _mouses.insert(std::make_pair(touch->getID(), mouse));
        
        return true;
    }
    
    return false;
}

void ParaScene::onTouchMoved(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        it->second->setPosition(touch->getLocation());
    }
}

void ParaScene::onTouchEnded(Touch* touch, Event* event)
{
    auto it = _mouses.find(touch->getID());
    
    if (it != _mouses.end())
    {
        this->removeChild(it->second);
        _mouses.erase(it);
    }
    
}


void ParaScene::update(float deltaTime)
{
    ProgressTimer* pTimer = (ProgressTimer*) this->getChildByTag(1);
    float per = pTimer->getPercentage();
    per += deltaTime*10;
    if(per > 100){
        per = 100;
        this->unscheduleUpdate();
    }
    pTimer->setPercentage(per);
}


void ParaScene::menuCloseCallBack(cocos2d::Ref *pSnder)
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
