//
//  Entity.cpp
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#include "Entity.h"

bool Entity::init() {
    if (!Layer::init()) {
        return false;
    }
    
    graphic = Sprite::create("close_normal.png");
    addChild(graphic);
    
    return true;
}