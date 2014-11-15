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
    if (!Layer::init()) {
        return false;
    }
    
    sprite = Sprite::create("close_normal.png");
    this->addChild(sprite);
    this->setContentSize(Size::ZERO);
    
    return true;
}