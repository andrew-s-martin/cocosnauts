//
//  FuelBar.h
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#ifndef __Cocosnauts__FuelBar__
#define __Cocosnauts__FuelBar__

#include "cocos2d.h"

USING_NS_CC;

class FuelBar : public Sprite {
public:
    FuelBar();
    virtual bool init();
    CREATE_FUNC(FuelBar);
    void setFillMultiplier(float fillMultiplier);
private:
    Color3B fullCol, emptyCol;
    float fillMultiplier; // 0.0 to 1.0
};

#endif /* defined(__Cocosnauts__FuelBar__) */
