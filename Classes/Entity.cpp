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
    this->setContentSize(Size::ZERO);
    return true;
}

bool Entity::intersect(Vec2 pos, float radius) {
    return false;
}

void Entity::addOrbit(Orbit*o) {
    o->e->setPositionX(o->radius*getUnitOrbitRadius());
    this->addChild(o->e);
    this->orbits.push_back(o);
}

void Entity::updateOrbits(float dt) {
    for (auto o : orbits) {
        o->curAngle += o->speed * 2 * M_PI * dt;
        auto parentRadius = getUnitOrbitRadius();
        float x = cosf(o->curAngle) * o->radius * parentRadius;
        float y = sinf(o->curAngle) * o->radius * parentRadius;
        o->e->setPosition(x, y);
        o->e->updateOrbits(dt);
    }
}

float Entity::getUnitOrbitRadius() {
    return 0;
}