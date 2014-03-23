//
//  Bat.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-14.
//
//

#include "BatLayer.h"
#include "MainScene.h"

#define RATIO  48.0f

USING_NS_CC;

BatLayer *BatLayer::sharedBatLayer = NULL;

BatLayer::~BatLayer()
{
    score = 0;
    bat = NULL;
}

bool BatLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        bRet = true;
        
        batinit();
        
    } while (0);
    
    
    return bRet;
}

void BatLayer::batinit()
{

    bat = CCPhysicsSprite::createWithSpriteFrameName("board_nomal1.png");
    
    b2World *world = MainScene::SharedWorld();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize size = bat->getContentSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position = b2Vec2(winSize.width/2/RATIO, winSize.height * 0.1 /RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2PolygonShape batShape;
    batShape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
    
    b2FixtureDef batFixtureDef;
    batFixtureDef.shape = &batShape;
    batFixtureDef.userData = NULL;
    batFixtureDef.density = 10000.0f;
    body->CreateFixture(&batFixtureDef);
    
    bat->setB2Body(body);
    bat->setPTMRatio(RATIO);
    addChild(bat);
    
    CCBlink *blink = CCBlink::create(1, 3);
    CCAnimation *animation = CCAnimation::create();
    animation->setDelayPerUnit(0.1f);

    bat->runAction(blink);
}



//void BatLayer::MoveTo(cocos2d::CCPoint location)
//{
//    CCPoint actualPoint;
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    CCSize batSize = bat->getContentSize();
//    
//    if ( location.x < batSize.width/2 ) {
//        location.x = batSize.width/2;
//    }
//    if (location.x > winSize.width - batSize.width/2) {
//        location.x = winSize.width - batSize.width/2;
//    }
//    
//    if (location.y < batSize.height/2) {
//        location.y = batSize.height/2;
//    }
//    if (location.y > winSize.height - batSize.height/2) {
//        location.y = winSize.height - batSize.height/2;
//    }
//    
//    bat->setPosition(location);
//}

