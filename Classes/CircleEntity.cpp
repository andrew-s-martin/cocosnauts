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

void CircleEntity::setColor(const cocos2d::Color3B &col) {
    sprite->setColor(col);
}

bool CircleEntity::intersect(Entity*other) {
    auto ePos = other->getPosition();
    auto eRadius = other->getUnitOrbitRadius();
    auto distance = this->getPosition().distance(ePos);
    auto thisRadius = this->getUnitOrbitRadius();
    return distance < (thisRadius + eRadius);
}

float CircleEntity::getUnitOrbitRadius() {
    return sprite->getContentSize().height/2 * this->getScale();
}