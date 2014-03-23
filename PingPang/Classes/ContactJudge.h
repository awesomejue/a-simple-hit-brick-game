//
//  ContactJudger.h
//  PingPang
//
//  Created by lanou3g on 14-3-14.
//
//

#ifndef __PingPang__ContactJudger__
#define __PingPang__ContactJudger__

#include "Box2D.h"
#include <set>
#include <vector>

#include "cocos-ext.h"
USING_NS_CC_EXT;

class MainScene;

class ContactJudge : public b2ContactListener {
    
public:
    ContactJudge():main(NULL){}
    ContactJudge(MainScene *main):main(main){}
    ~ContactJudge();
    
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
    std::set<CCPhysicsSprite *>contacts;
private:
    MainScene *main;
};

#endif /* defined(__PingPang__ContactJudger__) */
