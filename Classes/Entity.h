//
//  Entity.h
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#ifndef __test__Entity__
#define __test__Entity__

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Layer {
public:
    Entity();
    virtual bool init();
    CREATE_FUNC(Entity);
    
    class Orbit {
    public:
        float radius, speed, curAngle;
        bool clockwise;
        Entity *e;
    };
    
    Vec2 vel;
    float maxSpeed, mass;
    std::vector<Orbit*> orbits;
    Sprite* sprite;
};

#endif /* defined(__test__Entity__) */
