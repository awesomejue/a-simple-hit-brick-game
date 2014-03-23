//
//  WarLayer.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#include "WarLayer.h"
#include "MainScene.h"
//#include "CCPhysicsSprite.h"

#define RATIO  48.0f

USING_NS_CC;


WarLayer::WarLayer()
{
    
}

WarLayer::~WarLayer()
{
    ball = NULL;
}

bool WarLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(! CCLayer::init());
        ballinit();
        bricksinit(1);
        scheduleUpdate();
        bRet = true;
    } while (0);
    
    return bRet;
}

void WarLayer::ballinit()
{

    b2World *world = MainScene::SharedWorld();

    ball = CCPhysicsSprite::createWithSpriteFrameName("ball_fire.png");
    CCSize size = ball->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.position = b2Vec2(winSize.width/2/RATIO, winSize.height*0.13 /RATIO);

    bodyDef.linearVelocity = b2Vec2(0.0, -10.0);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
//    b2PolygonShape ballShape;
//    ballShape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
    b2CircleShape ballShape;
    ballShape.m_radius = (size.width > size.height ? size.height:size.width)/2.0/RATIO;
    
    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 0.1f;
    ballFixtureDef.restitution = true;
    body->CreateFixture(&ballFixtureDef);
    
    ball->setB2Body(body);
    ball->setPTMRatio(RATIO);
    addChild(ball);
    
}

void WarLayer::bricksinit(int level)
{
    
    for (int j = 0; j != level; ++j) {
        
        for (int i = 0; i != 26; ++i) {
            
            CCString block;
            block.initWithFormat("block%i.png", arc4random()%8 +1);
            CCPhysicsSprite *brick = CCPhysicsSprite::createWithSpriteFrameName(block.getCString());
            CCSize size = brick->getContentSize();
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position = b2Vec2((60.0f+i*size.width)/RATIO, (540.0 - j*size.height)/RATIO);
            b2Body *body = MainScene::SharedWorld()->CreateBody(&bodyDef);
            b2PolygonShape shape;
            shape.SetAsBox(size.width/2/RATIO, size.height/2/RATIO);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.userData = brick;
            body->CreateFixture(&fixtureDef);
            brick->setB2Body(body);
            brick->setPTMRatio(RATIO);
            addChild(brick);
        }
    }
    
}


void WarLayer::update(float dt)
{
    if (getChildren()->count() == 1) {
        MainScene *layer = dynamic_cast<MainScene *>(getParent());
        layer->nextLevel();
    }
}




