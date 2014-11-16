//
//  Ship.h
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#ifndef __Test__Ship__
#define __Test__Ship__

#include <stdio.h>
#include "Entity.h"

class Ship : public Entity {
public:
    virtual bool init();
    CREATE_FUNC(Ship);
    float getFuel();
    void setFuel(float pFuel);
    
private:
    float aFuel;
};



#endif /* defined(__Test__Ship__) */
