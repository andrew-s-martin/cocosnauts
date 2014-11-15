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
    virtual bool init();
    CREATE_FUNC(Entity);
    
    Vec2 pos, vel;
    float maxSpeed;
    Sprite* graphic;
};

#endif /* defined(__test__Entity__) */
