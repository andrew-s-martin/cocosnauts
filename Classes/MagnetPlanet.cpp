//
//  MagnetPlanet.cpp
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#include "MagnetPlanet.h"

bool MagnetPlanet::init() {
    if(!Entity::init()) {
        return false;
    }
    
    sprite = Sprite::create("close_normal.png");
    this->addChild(sprite);
    
    return true;
}

float MagnetPlanet::getMagnetism(){
    return aMagnetism;
}

void MagnetPlanet::setMagnetism(float pMagnetism){
    aMagnetism = pMagnetism;
}

//bool MagnetPlanet::intersect(cocos2d::Vec2 pos, float radius, cocos2d::Vec2 coll) {
//    auto distance = coll.distance(pos);
//    auto thisRadius = this->getRadius();
//    if (distance < (thisRadius + radius)) return true;
//    
//    for (auto o : orbits) {
//        if (o->e->intersect(convertToNodeSpace(pos), radius)) {
//            return true;
//        }
//    }
//    return false;
//}
