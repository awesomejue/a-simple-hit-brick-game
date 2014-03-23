//
//  GameOverScene.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#include "GameOverScene.h"
#include "WelcomScene.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"

using namespace std;
USING_NS_CC;

bool GameOverScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF( ! CCLayer::init() );
        setTouchEnabled(true);
        bRet = true;
        
        bgInit();
    } while (0);
    
    return bRet;
}

CCScene *GameOverScene::scene()
{
    CCScene *pScene = CCScene::create();
    CCLayer *pLayer = GameOverScene::create();
    
    pScene->addChild(pLayer);
    
    return pScene;
}

void GameOverScene::onEnter()
{
    CCLayer::onEnter();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background3.mp3");
    cout<<CCUserDefault::sharedUserDefault()->getIntegerForKey("score")<<endl;
}

void GameOverScene::onExit()
{
    CCLayer::onExit();
}

void GameOverScene::bgInit()
{
    CCSprite *background3 = CCSprite::create("bg_ingame3.jpg");
    background3->setScale(2.2);
    background3->setPosition(ccp(480.0,320.0));
    addChild(background3);
    
    CCLabelTTF *gameover = CCLabelTTF::create("游戏结束", "Arial", 62.0f);
    gameover->setPosition(ccp(VisibleRect::center().x, (VisibleRect::top().y + VisibleRect::center().y)/2.0));
    addChild(gameover);
    
    int score = CCUserDefault::sharedUserDefault()->getIntegerForKey("score");
    int higest_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("higest_score");
    if (score > higest_score) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("higest_score", score);
    }
    
    CCLabelTTF *scoreLabel = CCLabelTTF::create("你的分数：", "Arial", 42.0f);
    CCString *scoreString = CCString::createWithFormat("你的分数：%i", CCUserDefault::sharedUserDefault()->getIntegerForKey("score"));
    scoreLabel->setString(scoreString->getCString());
    scoreLabel->setPosition(VisibleRect::center());
    addChild(scoreLabel);
    
    CCLabelTTF *higest_scoreLabel = CCLabelTTF::create("最高分数：", "Arial", 42.0f);
    CCString *higest_scoreString = CCString::createWithFormat("最高分数：%i", CCUserDefault::sharedUserDefault()->getIntegerForKey("higest_score"));
    higest_scoreLabel->setString(higest_scoreString->getCString());
    higest_scoreLabel->setPosition(ccp(VisibleRect::center().x, scoreLabel->getPositionY() - higest_scoreLabel->getContentSize().height - 20.0f));
    addChild(higest_scoreLabel);
}

void GameOverScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

    CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInB::create(1.0, WelcomScene::scene()));
}


