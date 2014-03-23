//
//  WelcomScene.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#include "WelcomScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"

USING_NS_CC;


bool WelcomScene::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSprite *background1 = CCSprite::create("bg_ingame1.jpg");
        background1->setScale(2.2);
        background1->setPosition(ccp(480.0,320.0));
        addChild(background1);

        setTouchEnabled(true);
        preloadMusic();
        preloadImage();
        setTouchEnabled(true);
        bginit();
        bRet = true;
    } while (0);
    
    return bRet;
}

WelcomScene::~WelcomScene()
{

}



CCScene *WelcomScene::scene()
{
    CCScene *pScene = CCScene::create();
    CCLayer *pLayer = WelcomScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}


void WelcomScene::onEnter()
{
    CCLayer::onEnter();


    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background1.wav", true);
}

void WelcomScene::onExit()
{
    CCLayer::onExit();
}

void WelcomScene::bginit()
{
    CCControlButton *play = CCControlButton::create("开始游戏", "Arail", 64.0f);
    play->setPosition(VisibleRect::center());
    play->addTargetWithActionForControlEvents(this, cccontrol_selector(WelcomScene::nextScene), CCControlEventTouchUpInside);
    addChild(play);
    
    CCParticleFire *magic_fire = CCParticleFire::createWithTotalParticles(250);
    magic_fire->setPosition(VisibleRect::bottom());
    addChild(magic_fire);
    
    CCParticleRain *magic_rain = CCParticleRain::createWithTotalParticles(250);
    addChild(magic_rain);
    
}

void WelcomScene::nextScene()
{
    CCScene *main = MainScene::scene();
    CCTransitionMoveInB *animateScene = CCTransitionMoveInB::create(1.0f, main);
    CCDirector::sharedDirector()->replaceScene(animateScene);
}



void WelcomScene::preloadMusic()
{
    CocosDenshion::SimpleAudioEngine *engine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    engine->preloadBackgroundMusic("background1.wav");
    engine->preloadBackgroundMusic("background2.mp3");
    engine->preloadBackgroundMusic("background3.mp3");
    engine->preloadBackgroundMusic("game_over.wav");
    engine->preloadEffect("eat.wav");
}

void WelcomScene::preloadImage()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gamesext.plist", "gamesext.png");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("start.plist", "start.png");
}






