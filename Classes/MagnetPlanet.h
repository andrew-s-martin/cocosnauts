//
//  MagnetPlanet.h
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#ifndef __Test__MagnetPlanet__
#define __Test__MagnetPlanet__

#include <stdio.h>
#include "CircleEntity.h"

class MagnetPlanet: public CircleEntity {
public:
    virtual bool init();
    CREATE_FUNC(MagnetPlanet);
    
    void setSprite();
    void setMagnetism(float pMagnetism);
    float getMagnetism();
    bool intersect(Vec2 pos, float radius, Vec2 coll);
private:
    int aCounter;
    float aMagnetism;
};

#endif /* defined(__Test__MagnetPlanet__) */
