//
//  Ship.h
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#ifndef __Test__Ship__
#define __Test__Ship__

#include "CircleEntity.h"

class Ship : public CircleEntity {
public:
    virtual bool init();
    CREATE_FUNC(Ship);
    float getFuel();
    void setFuel(float pFuel);
    void setMaxFuel(float pMaxFuel);
    float getFuelPercent();
    
private:
    Sprite* triangle;
    float aFuel, maxFuel;
};



#endif /* defined(__Test__Ship__) */
