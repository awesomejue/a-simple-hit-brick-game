//
//  MainScene.h
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#ifndef __PingPang__MainScene__
#define __PingPang__MainScene__

#include <cocos2d.h>
#include "Box2D.h"
#include "ContactJudge.h"

class BatLayer;
class WarLayer;

class MainScene : public cocos2d::CCLayer, public b2ContactListener {
public:
    virtual bool init();
    MainScene();
    ~MainScene();
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(MainScene)
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
//    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void nextLevel();
    
    void timepast(float dt);
    void update(float dt);
    
    static b2World *SharedWorld();
    
    cocos2d::CCArray *array;
    
    bool isAlive();
    int score();
    
private:
    
    WarLayer *warLayer;
    BatLayer *batLayer;
    cocos2d::CCLabelTTF *levelBoard;
    cocos2d::CCLabelTTF *scoreBoard;
    cocos2d::CCLabelTTF *timeBoard;
    void boardinit();
    void worldinit();
    
    ContactJudge *judge;
    
    int _score;
    bool _alive;
};


extern const char *GAME_OVER;

#endif /* defined(__PingPang__MainScene__) */
