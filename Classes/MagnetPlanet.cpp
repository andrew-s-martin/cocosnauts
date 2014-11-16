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
