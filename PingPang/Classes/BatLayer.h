//
//  Bat.h
//  PingPang
//
//  Created by lanou3g on 14-3-14.
//
//

#ifndef __PingPang__Bat__
#define __PingPang__Bat__

#include <cocos2d.h>
#include "cocos-ext.h"
#include "Box2D.h"

USING_NS_CC_EXT;

class BatLayer : public cocos2d::CCLayer {
public:
    
    BatLayer():score(0){}
    ~BatLayer();
    
    virtual bool init();
    
    CREATE_FUNC(BatLayer)
    
//    void MoveTo(cocos2d::CCPoint location);
    
    static BatLayer *sharedBatLayer;
    
    
    int score;
    
     CCPhysicsSprite *bat;
    
private:
    void batinit();
    
};

#endif /* defined(__PingPang__Bat__) */
