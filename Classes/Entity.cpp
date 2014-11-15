//
//  Entity.cpp
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#include "Entity.h"

Entity::Entity() :
mass(1)
{ }

bool Entity::init() {
    if (!Sprite::initWithFile("close_normal.png")) {
        return false;
    }
    this->setAnchorPoint(Vec2(0.5, 0.5));
    return true;
}