//
//  MainScene.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#include "MainScene.h"
#include "BatLayer.h"
#include "WarLayer.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "GameOverScene.h"

#define RATIO 48.0f

USING_NS_CC;

const char *GAME_OVER = "game_over";

b2World *world = NULL;

b2World *MainScene::SharedWorld()
{
    if (!world) {
        
        b2Vec2 gravity;
        gravity.Set(0.0f, 0.0f);
        world = new b2World(gravity);
        world->SetAllowSleeping(true);
        world->SetContinuousPhysics(true);
        
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0, 0);
        
        b2Body *groundBody = world->CreateBody(&groundBodyDef);
        b2EdgeShape groundBox;
        
        b2Fixture *fixture;
        // top
        
        groundBox.Set(b2Vec2(VisibleRect::leftTop().x/RATIO,560.0/RATIO), b2Vec2(VisibleRect::rightTop().x/RATIO,560.0/RATIO));
        fixture = groundBody->CreateFixture(&groundBox,0);
        fixture->SetFriction(.0f);
//        fixture->
        
        // left
        groundBox.Set(b2Vec2(VisibleRect::leftTop().x/RATIO,VisibleRect::leftTop().y/RATIO), b2Vec2(VisibleRect::leftBottom().x/RATIO,VisibleRect::leftBottom().y/RATIO));
        groundBody->CreateFixture(&groundBox,0)->SetFriction(0.0);
        
        // right
        groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/RATIO,VisibleRect::rightBottom().y/RATIO), b2Vec2(VisibleRect::rightTop().x/RATIO,VisibleRect::rightTop().y/RATIO));
        groundBody->CreateFixture(&groundBox,0)->SetFriction(0.0);
        
     
        return world;
    }

    return world;
}


bool MainScene::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        bRet = true;
        
        _alive = true;
        _score = 0;
        
        CCSprite *background2 = CCSprite::create("bg_ingame2.jpg");
        background2->setScale(2.2);
        background2->setPosition(ccp(480.0,320.0));
        addChild(background2);
        
        boardinit();
        MainScene::SharedWorld();
        worldinit();
        setTouchEnabled(true);
        scheduleUpdate();
        
        batLayer = BatLayer::create();
        batLayer->setPosition(CCPointZero);
        this->addChild(batLayer);
        
        warLayer = WarLayer::create();
        warLayer->setPosition(CCPointZero);
        this->addChild(warLayer);
        
    } while (0);
    
    return bRet;
}

bool MainScene::isAlive()
{
    return _alive;
}

int MainScene::score()
{
    return _score;
}

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    delete judge;
    judge = NULL;
}

CCScene * MainScene::scene()
{
    CCScene *pScene = CCScene::create();
    
    CCLayer *pLayer = MainScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}


void MainScene::onEnter()
{
    CCLayer::onEnter();

    schedule(schedule_selector(MainScene::timepast), 1.0f);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background2.mp3");
    
    
//    CCControlButton *button = CCControlButton::create("测试", "Arial", 42);
//    button->addTargetWithActionForControlEvents(this, cccontrol_selector(MainScene::nextLevel), CCControlEventTouchUpInside);
//    button->setPosition(VisibleRect::center());
//    addChild(button , 10);
    
    
}

void MainScene::worldinit()
{
    judge = new ContactJudge(this);
    MainScene::SharedWorld()->SetContactListener(judge);
}

void MainScene::boardinit()
{
    scoreBoard = CCLabelTTF::create("分数：0", "Alias", 38.0f);
    scoreBoard->setPosition(ccp(140, 580));
    this->addChild(scoreBoard);
    
    timeBoard = CCLabelTTF::create("时间：0", "Alias", 38.0f);
    timeBoard->setPosition(ccp(780, 580));
    this->addChild(timeBoard);
    
    levelBoard = CCLabelTTF::create("Level：1", "Alias", 38.0f);
    levelBoard->setPosition(ccp(480, 580));
    this->addChild(levelBoard);
    
    
    CCParticleSnow *magic_snow = CCParticleSnow::createWithTotalParticles(20);
    addChild(magic_snow);
}

void MainScene::onExit()
{
    CCLayer::onExit();
}

void MainScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MainScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(pTouch->getLocation().x < winSize.width/2)
    {
        batLayer->bat->getB2Body()->SetLinearVelocity(b2Vec2(-5.0,0));
    }
    else
    {
        batLayer->bat->getB2Body()->SetLinearVelocity(b2Vec2(5.0,0));
    }
    
    return true;
}


void MainScene::nextLevel()
{
    static int level = 1;
    ++level;
    CCString levelString;
    levelString.initWithFormat("Level：%i", level);
    levelBoard->setString(levelString.getCString());
    
    warLayer->bricksinit(level);
}

void MainScene::timepast(float dt)
{
    static int timepast = 0;
    ++timepast;
    CCString timeString;
    timeString.initWithFormat("时间：%i", timepast);
    timeBoard->setString(timeString.getCString());
}

void MainScene::update(float dt)
{
    
    int velocityIterations = 8;
    int positionIterations = 3;
    MainScene::SharedWorld()->Step(dt, velocityIterations, positionIterations);
    
    if(warLayer->ball->getPositionY() < batLayer->bat->getPositionY())
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(GAME_OVER);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("score", _score);
        _alive = false;
        CCScene *gameover = GameOverScene::scene();
        CCTransitionMoveInB *animateScene = CCTransitionMoveInB::create(1.0f, gameover);
        CCDirector::sharedDirector()->replaceScene(animateScene);
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    
    if(batLayer->bat->getPositionX() - batLayer->bat->getContentSize().width/2 <= 0 || batLayer->bat->getPositionX() + batLayer->bat->getContentSize().width/2 >= winSize.width)
    {
        batLayer->bat->getB2Body()->SetLinearVelocity(b2Vec2(.0f, .0f));
    }

    
    std::set<CCPhysicsSprite *>::iterator pos;
    for (pos = judge->contacts.begin(); pos != judge->contacts.end(); ++pos) {
        MainScene::SharedWorld()->DestroyBody((*pos)->getB2Body());
        (*pos)->removeFromParentAndCleanup(true);
        _score++;
    }
    judge->contacts.clear();
    
    CCPhysicsSprite *ball = warLayer->ball;
    b2Vec2 velocity = ball->getB2Body()->GetLinearVelocity();
    if (velocity.Length()<10.0) {
        ball->getB2Body()->SetLinearVelocity(b2Vec2(10.0*(velocity.x/velocity.Length()),10.0*(velocity.y/velocity.Length())));
    }
    
    CCString *scoreTMP = CCString::createWithFormat("分数：%i", _score);
    scoreBoard->setString(scoreTMP->getCString());
}





