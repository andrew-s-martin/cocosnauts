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
    if (!Sprite::initWithFile("9_sprite_square.png")) {
        return false;
    }
    _defaultSize = this->getTextureRect().size;
    setAnchorPoint(Vec2(0, 1));
    setColor(fullCol);
    
    return true;
}

void FuelBar::setHeight(int height) {
    setScaleY(height/_defaultSize.height);
}

void FuelBar::setMaxWidth(int width) {
    maxWidth = width;
    setScaleX(maxWidth/_defaultSize.width);
    setColor(fullCol);
}

void FuelBar::setFillMultiplier(float fillMultiplier) {
    fillMultiplier = fillMultiplier;
    setColor(Color3B(255*(1-fillMultiplier), 255*fillMultiplier, 0));
    setScaleX(fillMultiplier * maxWidth/_defaultSize.width);
}