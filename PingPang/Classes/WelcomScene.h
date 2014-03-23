//
//  WelcomScene.h
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#ifndef __PingPang__WelcomScene__
#define __PingPang__WelcomScene__

#include <cocos2d.h>

class WelcomScene : public cocos2d::CCLayer {
public:
    
    ~WelcomScene();
    
    virtual bool init();
    
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(WelcomScene)
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void bginit();
    void preloadMusic();
    void preloadImage();
    
private:
    void nextScene();
};

#endif /* defined(__PingPang__WelcomScene__) */
