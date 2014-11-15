//
//  Entity.cpp
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#include "Entity.h"

Entity::Entity() :
mass(1),
respondToGravity(false)
{ }

bool Entity::init() {
    if (!Sprite::initWithFile("close_normal.png")) {
        return false;
    }
    return true;
}