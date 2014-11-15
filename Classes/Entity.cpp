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

void Entity::updateOrbits(float dt) {
    for (auto o : orbits) {
        o->curAngle += o->speed * 2 * M_PI * dt;
        auto parentRadius = sprite->getContentSize().height/2;
        float x = cosf(o->curAngle) * o->radius * parentRadius;
        float y = sinf(o->curAngle) * o->radius * parentRadius;
        o->e->setPosition(x, y);
        o->e->updateOrbits(dt);
    }
}