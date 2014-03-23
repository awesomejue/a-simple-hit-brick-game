//
//  ContactJudger.cpp
//  PingPang
//
//  Created by lanou3g on 14-3-14.
//
//

#include "ContactJudge.h"

#include "MainScene.h"

#include "SimpleAudioEngine.h"


ContactJudge::~ContactJudge()
{
    
}

void ContactJudge::BeginContact(b2Contact *contact)
{

    
}

void ContactJudge::EndContact(b2Contact *contact)
{
    
}

void ContactJudge::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
//    b2WorldManifold worldMainfold;
//    contact->GetWorldManifold(&worldMainfold);
    
}

void ContactJudge::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

    if ( contact->GetFixtureA()->GetUserData() ) {
        contacts.insert(static_cast<CCPhysicsSprite *>(contact->GetFixtureA()->GetUserData()));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eat.wav");
    }
    if ( contact->GetFixtureB()->GetUserData() ) {
        contacts.insert(static_cast<CCPhysicsSprite *>(contact->GetFixtureB()->GetUserData()));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eat.wav");
    }
    
}





