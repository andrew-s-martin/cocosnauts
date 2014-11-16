//
//  Ship.cpp
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#include "Ship.h"


float Ship::getFuel(){
    return aFuel;
}

void Ship::setFuel(float pFuel) {
    aFuel = pFuel;
}

bool Ship::init() {
    if (!Entity::init()) {
        return false;
    }
    
    sprite = Sprite::create("triangle.png");
    aFuel = 10.0;
    this->addChild(sprite);
    
    return true;
}
