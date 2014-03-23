//
//  WarLayer.h
//  PingPang
//
//  Created by lanou3g on 14-3-13.
//
//

#ifndef __PingPang__WarLayer__
#define __PingPang__WarLayer__

#include <cocos2d.h>
#include "cocos-ext.h"
#include "Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;

class WarLayer : public cocos2d::CCLayer {
    
public:
    
    WarLayer();
    ~WarLayer();
    virtual bool init();
    CREATE_FUNC(WarLayer);
    CCPhysicsSprite *ball;
    
    void update(float dt);
    
    void bricksinit(int level);
private:
    
    void ballinit();
};

#endif /* defined(__PingPang__WarLayer__) */
