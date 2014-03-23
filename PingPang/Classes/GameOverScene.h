//
//  GameOverScene.h
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#ifndef __PingPang__GameOverScene__
#define __PingPang__GameOverScene__

#include <cocos2d.h>

class GameOverScene : public cocos2d::CCLayer {
public:
    virtual bool init();
    static cocos2d::CCScene *scene();
    CREATE_FUNC(GameOverScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
private:
    void bgInit();
};

#endif /* defined(__PingPang__GameOverScene__) */
