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
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = ParaScene::create();
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
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(ParaScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(ParaScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(ParaScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

Node* ParaScene::makeBall(Vec2 point, float radius, PhysicsMaterial material)
{
    Node* ball = Node::create();
    ball->setContentSize(Size(50, 50));
    material.density = 0.5f;
    material.friction = 0.5f;
    material.restitution = 0.5f;
    auto body = PhysicsBody::createCircle(radius, material);
    ball->setPhysicsBody(body);
    ball->setPosition(Vec2(point.x, point.y));
    
    return ball;
}

void ParaScene::onEnter(){
    Layer::onEnter();
    
    //setPhyWorld(dynamic_cast<Scene*>(this->getParent())->getPhysicsWorld());
    setScene(dynamic_cast<Scene*>(this->getParent()));
    
    Size vSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //time progress bar
    Sprite* tSp = Sprite::create("Light_mini_On.png");
    ProgressTimer* pTimer = ProgressTimer::create(tSp);
    pTimer->setType(ProgressTimer::Type::RADIAL); //watch type
    pTimer->setPosition(Vec2(vSize.width/2, vSize.height/2));
    pTimer->setPercentage(0.0f);
    pTimer->setTag(1);
    pTimer->setPhysicsBody(PhysicsBody::createCircle(tSp->getContentSize().width/2-5));
    pTimer->getPhysicsBody()->setMass(0.1f);
    this->addChild(pTimer,5);
    
    this->scheduleUpdate();
    
    /*
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
     */
    
    auto player = Sprite::create("title2.png");
    auto pb = PhysicsBody::createBox(Size(player->getContentSize()));
    pb->setEnable(true);
    pb->setRotationEnable(true);
    pb->setTag(55);
    pb->setMass(0.1f);
    player->setPosition(Vec2(220, 400));
    player->setPhysicsBody(pb);
    
    this->addChild(player,50,1);
    
    
    
    auto fem = Scale9Sprite::create("f113f.png");
    fem->setScale(0.15f);
    fem->setPhysicsBody(PhysicsBody::createBox(Size(fem->getContentSize().width*0.13f,
                                                    fem->getContentSize().height*0.13f)));
    fem->getPhysicsBody()->setMass(100);
    
    fem->setPosition(Vec2(400, 200));
    fem->getPhysicsBody()->setTag(55);
    fem->setTag(22);
    this->addChild(fem);

    auto sp1 = makeBall(Vec2(230, 80), 10,PHYSICSBODY_MATERIAL_DEFAULT);
    sp1->getPhysicsBody()->setTag(55);
    auto sp2 = makeBall(Vec2(260, 80), 10,PHYSICSBODY_MATERIAL_DEFAULT);
    sp2->getPhysicsBody()->setTag(55);
    
    PhysicsJointPin* joint = PhysicsJointPin::construct(sp1->getPhysicsBody(), sp2->getPhysicsBody(), Vec2(230, 80));
    _scene->getPhysicsWorld()->addJoint(joint);
    
    this->addChild(sp1);
    this->addChild(sp2);

 
    //bridge
    Node* prb = nullptr;
    for(int i = 0;i < 50;i++){
        Vec2 offset(i*20.5f,160);
        auto br = Node::create();
        br->setContentSize(Size(20, 7));
        br->setPosition(offset+Vec2(10.5f, 0));
        
        PhysicsMaterial cm;
        cm.density = 1;
        cm.friction = 0.5f;
        cm.restitution = 1;
        
        auto bb = PhysicsBody::createBox(Size(20, 7),cm);
        bb->setMass(2);
        //bb->setLinearDamping(1);
        bb->setAngularVelocityLimit(0.5f);
        //bb->setAngularDamping(0.1f);
        bb->setVelocityLimit(0.5f);
        br->setPhysicsBody(bb);

        if(i == 0 || i == 50-1){
            bb->setDynamic(false);
        }
        this->addChild(br);
        
        if(prb){
            PhysicsJointDistance* joint = PhysicsJointDistance::construct(prb->getPhysicsBody(), br->getPhysicsBody(), Vec2(10, 0),Vec2(-10,0));
            joint->setDistance(0);
            
            PhysicsJointPin* joint2 = PhysicsJointPin::construct(prb->getPhysicsBody(), br->getPhysicsBody(), offset);
            
            _scene->getPhysicsWorld()->addJoint(joint2);
        }
        prb = br;
    }
    
    cam = new ActionCamera;
    cam->startWithTarget(this);
}




bool ParaScene::onTouchBegan(Touch* touch, Event* event)
{
    
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
    
    if(body) CCLOG("x:%f y:%f",body->getPosition().x,body->getPosition().y);
        
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
    //this->setPosition(ap->getPosition());
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
        //this->unscheduleUpdate();
    }
    pTimer->setPercentage(per);
    
    auto ap = (Sprite*)this->getChildByTag(22);
    cam->setEye(ap->getPosition().x, ap->getPosition().y, 0);
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
