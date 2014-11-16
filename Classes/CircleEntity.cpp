//
//  CircleEntity.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#include "CircleEntity.h"

bool CircleEntity::init() {
    if(!Entity::init()) {
        return false;
    }
    
    sprite = Sprite::create("close_normal.png");
    this->addChild(sprite);
    
    return true;
}

bool CircleEntity::intersect(Vec2 pos, float radius) {
    auto distance = this->getPosition().distance(pos);
    auto thisRadius = this->getRadius();
    if (distance < (thisRadius + radius)) return true;
    
    for (auto o : orbits) {
        if (o->e->intersect(convertToNodeSpace(pos), radius)) {
            return true;
        }
    }
    return false;
}

float CircleEntity::getUnitOrbitRadius() {
    return sprite->getContentSize().height * this->getScale();
}

void CircleEntity::setColor(const cocos2d::Color3B &col) {
    sprite->setColor(col);
}

float CircleEntity::getRadius() {
    return sprite->getContentSize().height/2 * this->getScale();
}