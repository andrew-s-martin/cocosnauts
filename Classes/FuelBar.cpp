//
//  FuelBar.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#include "FuelBar.h"

FuelBar::FuelBar() :
fullCol(Color3B::GREEN),
emptyCol(Color3B::RED),
fillMultiplier(1.0)
{ }

bool FuelBar::init() {
    if (Sprite::initWithFile("9_sprite_square.png")) {
        return false;
    }
    this->setColor(fullCol);
    
    return true;
}

void FuelBar::setFillMultiplier(float fillMultiplier) {
    this->fillMultiplier = fillMultiplier;
    this->setColor(Color3B(255*fillMultiplier, 255*(1-fillMultiplier), 0));
}